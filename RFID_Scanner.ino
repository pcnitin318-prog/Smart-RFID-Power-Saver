#include <SPI.h>
#include <MFRC522.h>

// Pins assigned as per wiring
#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();       // Init SPI bus
  rfid.PCD_Init();    // Init MFRC522 reader
  
  Serial.println("====================================");
  Serial.println("RFID Scanner Ready!");
  Serial.println("Card ko scanner ke paas laao...");
  Serial.println("====================================");
}

void loop() {
  // Look for new cards
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Print UID to Serial Monitor
  Serial.print("Tera Card UID (HEX): ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Halt PICC to stop re-reading until card is removed
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000);
}