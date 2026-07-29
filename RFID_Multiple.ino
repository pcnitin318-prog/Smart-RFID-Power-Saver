#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define RELAY_PIN 3

MFRC522 rfid(SS_PIN, RST_PIN);

// ===================================================================
// 📢 STEP: YAHAN APNE SARE CARDS KE NUMBERS DAALEIN!
// -------------------------------------------------------------------
// Aap jitne chahe utne cards add kar sakte hain, bas har card ke UID ko
// curly brackets {} me daal kar comma (,) se alag karte jayein.
// ===================================================================
byte authorizedCards[][4] = {
  {0x00, 0x00, 0x00, 0x00},  // 1st Card ka UID yahan dalein
  {0x00, 0x00, 0x00, 0x00},  // 2nd Card ka UID yahan dalein
  {0x00, 0x00, 0x00, 0x00}   // 3rd Card ka UID yahan dalein (Aur chahiye toh comma lagakar badha sakte hain)
};

// Auto-calculate kitne cards add kiye hain
const int totalCards = sizeof(authorizedCards) / sizeof(authorizedCards[0]);

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
  Serial.println("MULTIPLE KEYCARD SYSTEM INITIALIZED");
  Serial.print("Total Authorized Cards: ");
  Serial.println(totalCards);
  Serial.println("======================================");
}

void loop() {
  rfid.PCD_Init();

  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);

  if (rfid.PICC_WakeupA(bufferATQA, &bufferSize) == MFRC522::STATUS_OK) {
    if (rfid.PICC_ReadCardSerial()) {
      
      // Yahan hum check kar rahe hain ki scanned card hamari list me se kisi se match hota hai ya nahi
      if (checkMultipleUIDs(rfid.uid.uidByte)) {
        lastCardPresentTime = millis(); 

        if (!isPowerOn) {
          digitalWrite(RELAY_PIN, LOW); 
          isPowerOn = true;
          Serial.println("--> Authorized Card Resting: POWER ON");
        }
      } else {
        Serial.println("--> Unauthorized Card Detected! Access Denied.");
      }
      
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    }
  }

  if (isPowerOn && (millis() - lastCardPresentTime > cardTimeout)) {
    digitalWrite(RELAY_PIN, HIGH); 
    isPowerOn = false;
    Serial.println("--> Card Removed: POWER OFF");
  }

  delay(150); 
}

// Function jo scanned card ko hamari puri list se match karta hai
bool checkMultipleUIDs(byte *scanned) {
  for (int i = 0; i < totalCards; i++) {
    bool match = true;
    for (byte j = 0; j < 4; j++) {
      if (scanned[j] != authorizedCards[i][j]) {
        match = false;
        break;
      }
    }
    if (match) return true; // Agar kisi ek bhi card se match ho gaya toh true return karega
  }
  return false; // Agar kisi se match nahi hua
}