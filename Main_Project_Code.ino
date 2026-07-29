#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define RELAY_PIN 3

MFRC522 rfid(SS_PIN, RST_PIN);

// ===================================================================
// 📢 STEP: APNE CARD KA NUMBER YAHAN BADLEIN!
// -------------------------------------------------------------------
// 1. Pehle 'RFID_Scanner.ino' chalakar Serial Monitor par apna UID check karein.
// 2. Agar aapka UID aata hai (Jaise: A1 B2 C3 D4), toh use neeche aise likhein:
//    {0xA1, 0xB2, 0xC3, 0xD4}  <-- Har do letters ke pehle '0x' lagana hai.
// ===================================================================
byte masterUID[4] = {0x00, 0x00, 0x00, 0x00}; // <-- Apne card ka UID yahan dalein

unsigned long lastCardPresentTime = 0;
const unsigned long cardTimeout = 1200; 
bool isPowerOn = false;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); 

  Serial.println("======================================");
  Serial.println("HOTEL KEYCARD POWER SYSTEM RE-CONFIGURED");
  Serial.println("======================================");
}

void loop() {
  rfid.PCD_Init();

  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);

  if (rfid.PICC_WakeupA(bufferATQA, &bufferSize) == MFRC522::STATUS_OK) {
    if (rfid.PICC_ReadCardSerial()) {
      if (checkUID(rfid.uid.uidByte, masterUID)) {
        lastCardPresentTime = millis(); 

        if (!isPowerOn) {
          digitalWrite(RELAY_PIN, LOW); 
          isPowerOn = true;
          Serial.println("--> Card Resting: POWER ON [Line Active]");
        }
      }
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    }
  }

  if (isPowerOn && (millis() - lastCardPresentTime > cardTimeout)) {
    digitalWrite(RELAY_PIN, HIGH); 
    isPowerOn = false;
    Serial.println("--> Card Removed: POWER OFF [Line Cut]");
  }

  delay(150); 
}

bool checkUID(byte *scanned, byte *authorized) {
  for (byte i = 0; i < 4; i++) {
    if (scanned[i] != authorized[i]) {
      return false;
    }
  }
  return true;
}