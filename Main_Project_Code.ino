
#include <SPI.h>
#include <MFRC522.h>

// Pin Configuration
#define SS_PIN 10
#define RST_PIN 9
#define RELAY_PIN 3

// Initialize RFID Reader
MFRC522 rfid(SS_PIN, RST_PIN);

// Relay Configuration
// This configuration assumes an active-LOW relay module.
const byte RELAY_ON = LOW;
const byte RELAY_OFF = HIGH;

// Authorized RFID Card UID
// Replace these example values with your actual card UID.
const byte masterUID[] = {
  0xA1, 0xB2, 0xC3, 0xD4
};

// Card Detection Timeout
const unsigned long cardTimeout = 1200;

// System Variables
unsigned long lastCardPresentTime = 0;
bool isPowerOn = false;


// Check whether the scanned card is authorized
bool checkUID(byte *scannedUID, byte scannedSize) {

  if (scannedSize != sizeof(masterUID)) {
    return false;
  }

  for (byte i = 0; i < sizeof(masterUID); i++) {
    if (scannedUID[i] != masterUID[i]) {
      return false;
    }
  }

  return true;
}


// Control the relay
void setPower(bool state) {

  digitalWrite(RELAY_PIN, state ? RELAY_ON : RELAY_OFF);
  isPowerOn = state;

  if (state) {
    Serial.println("Authorized card detected: POWER ON");
  } else {
    Serial.println("Card removed or timed out: POWER OFF");
  }
}


void setup() {

  Serial.begin(9600);

  // Initialize relay in the OFF state
  digitalWrite(RELAY_PIN, RELAY_OFF);
  pinMode(RELAY_PIN, OUTPUT);

  // Initialize SPI communication and RFID reader
  SPI.begin();
  rfid.PCD_Init();

  delay(50);

  Serial.println("==================================");
  Serial.println("SMART RFID POWER SAVER");
  Serial.println("Automatic Power Control System");
  Serial.println("==================================");

  Serial.println("System initialized successfully.");
  Serial.println("Waiting for an authorized RFID card...");
}


void loop() {

  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);

  // Check whether an RFID card is present
  if (rfid.PICC_WakeupA(bufferATQA, &bufferSize) ==
      MFRC522::STATUS_OK) {

    // Read the card UID
    if (rfid.PICC_ReadCardSerial()) {

      // Verify the scanned UID
      if (checkUID(rfid.uid.uidByte, rfid.uid.size)) {

        // Update the last detected card time
        lastCardPresentTime = millis();

        // Activate the relay if it is currently OFF
        if (!isPowerOn) {
          setPower(true);
        }

      } else {

        Serial.println("Unauthorized RFID card detected.");

      }

      // Stop communication with the current card
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    }
  }

  // Turn OFF the relay if the authorized card
  // has not been detected within the timeout period
  if (isPowerOn &&
      (millis() - lastCardPresentTime >= cardTimeout)) {

    setPower(false);
  }

  delay(100);
}
