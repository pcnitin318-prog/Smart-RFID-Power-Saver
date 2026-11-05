
#include <SPI.h>
#include <MFRC522.h>

// Pin Configuration
#define SS_PIN 10
#define RST_PIN 9
#define RELAY_PIN 3

// Initialize RFID Reader
MFRC522 rfid(SS_PIN, RST_PIN);

// Relay Configuration
// Assumes an active-LOW relay module
const byte RELAY_ON = LOW;
const byte RELAY_OFF = HIGH;

// List of Authorized RFID Cards
// Replace these example UIDs with your actual card UIDs.
// All entries below are four-byte UIDs.

const byte authorizedCards[][4] = {

  {0xA1, 0xB2, 0xC3, 0xD4},  // First Card
  {0xE5, 0xF6, 0x12, 0x34},  // Second Card
  {0x78, 0x90, 0xAB, 0xCD}   // Third Card

};

// Automatically calculate the number of authorized cards
const byte totalCards =
  sizeof(authorizedCards) / sizeof(authorizedCards[0]);

// Card Detection Timeout
const unsigned long cardTimeout = 1200;

// System Variables
unsigned long lastCardPresentTime = 0;
bool isPowerOn = false;


// Check whether the scanned UID matches an authorized card
bool checkMultipleUIDs(byte *scannedUID, byte scannedSize) {

  // Check UID length
  if (scannedSize != 4) {
    return false;
  }

  // Compare scanned UID with all authorized cards
  for (byte i = 0; i < totalCards; i++) {

    bool match = true;

    for (byte j = 0; j < 4; j++) {

      if (scannedUID[j] != authorizedCards[i][j]) {
        match = false;
        break;
      }
    }

    if (match) {
      return true;
    }
  }

  return false;
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

  // Initialize relay in OFF state
  digitalWrite(RELAY_PIN, RELAY_OFF);
  pinMode(RELAY_PIN, OUTPUT);

  // Initialize SPI communication and RFID reader
  SPI.begin();
  rfid.PCD_Init();

  delay(50);

  Serial.println("====================================");
  Serial.println("SMART RFID POWER SAVER");
  Serial.println("MULTIPLE CARD ACCESS SYSTEM");
  Serial.println("====================================");

  Serial.print("Total Authorized Cards: ");
  Serial.println(totalCards);

  Serial.println("System initialized successfully.");
  Serial.println("Waiting for an authorized RFID card...");
}


void loop() {

  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);

  // Check for an RFID card
  if (rfid.PICC_WakeupA(bufferATQA, &bufferSize) ==
      MFRC522::STATUS_OK) {

    // Read card serial number
    if (rfid.PICC_ReadCardSerial()) {

      // Verify the scanned card
      if (checkMultipleUIDs(
            rfid.uid.uidByte,
            rfid.uid.size)) {

        // Update last authorized card detection time
        lastCardPresentTime = millis();

        // Turn ON relay if currently OFF
        if (!isPowerOn) {
          setPower(true);
        }

      } else {

        Serial.println("Unauthorized RFID card detected.");
        Serial.println("Access Denied.");

      }

      // Stop communication with the current card
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    }
  }

  // Turn OFF relay when no authorized card
  // has been detected within the timeout period
  if (isPowerOn &&
      (millis() - lastCardPresentTime >= cardTimeout)) {

    setPower(false);
  }

  delay(100);
}
