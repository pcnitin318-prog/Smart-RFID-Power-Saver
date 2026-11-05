# 🔋 Smart RFID Power Saver
### Automatic Power Cutoff System Using Arduino and RFID

![Arduino](https://img.shields.io/badge/Platform-Arduino_Uno-blue)
![Technology](https://img.shields.io/badge/Technology-RFID-green)
![Language](https://img.shields.io/badge/Language-C%2B%2B-orange)
![Project](https://img.shields.io/badge/Project-Semester%203-purple)

## 📌 Project Overview

The **Smart RFID Power Saver** is an Arduino-based energy management system designed to reduce unnecessary electricity consumption through RFID-based access control.

The system uses an Arduino Uno, an RC522 RFID reader, and a relay module to control an electrical load.

When an authorized RFID card is detected, the system activates the relay and enables the connected load. When the card is no longer detected within the configured monitoring period, the system deactivates the relay.

This project demonstrates the practical application of embedded systems, RFID technology, and automated power management.

## 🎯 Project Objectives

- Reduce unnecessary electricity consumption.
- Implement RFID-based access control.
- Automate electrical load switching.
- Support multiple authorized RFID cards.
- Demonstrate embedded system automation.
- Explore energy-efficient electrical control solutions.

## ⚙️ How It Works

1. The RC522 RFID reader scans a nearby RFID card.
2. The Arduino Uno reads the card's unique identification number (UID).
3. The Arduino compares the scanned UID with the list of authorized cards.
4. If the card is authorized, the relay is activated.
5. When the card is no longer detected within the configured monitoring period, the relay is deactivated.

**Note:** The RC522 detects cards within its reading range; it does not independently detect physical removal. The Arduino program must continuously monitor card presence and implement an appropriate timeout.

## 🛠️ Hardware Requirements

| Component | Description |
|---|---|
| Arduino Uno | Main microcontroller |
| RC522 RFID Module | RFID card reader |
| RFID Card / Key Fob | User identification |
| 5V Single-Channel Relay Module | Electrical load switching |
| Jumper Wires | Circuit connections |
| Breadboard | Prototyping |

## 💻 Software Requirements

- Arduino IDE
- SPI Library (included with Arduino IDE)
- MFRC522 RFID Library

### Installing the MFRC522 Library

1. Open Arduino IDE.
2. Navigate to **Sketch → Include Library → Manage Libraries**.
3. Search for `MFRC522`.
4. Select a compatible MFRC522 library, such as the GithubCommunity version.
5. Click **Install**.

The SPI library is already included in the Arduino IDE and does not require separate installation.

## 🔌 Circuit Connections

### 1. RC522 RFID Reader to Arduino Uno

| RC522 Pin | Arduino Uno Pin | Function |
|---|---|---|
| VCC | 3.3V | Power Supply |
| GND | GND | Ground |
| RST | Digital Pin 9 | Reset |
| SDA / SS | Digital Pin 10 | SPI Chip Select |
| MOSI | Digital Pin 11 | SPI Data Input |
| MISO | Digital Pin 12 | SPI Data Output |
| SCK | Digital Pin 13 | SPI Clock |
| IRQ | Not Connected | Not Required |

**Important:** The RC522 module operates at 3.3V. Never connect its VCC pin to the Arduino's 5V output. Check the module's signal-level requirements as well.

### 2. Relay Module to Arduino Uno

| Relay Pin | Arduino Uno Pin | Function |
|---|---|---|
| VCC | 5V | Power Supply |
| GND | GND | Ground |
| IN | Digital Pin 3 | Relay Control |

**Electrical Safety:** Household AC connections must be installed and tested by a qualified person using an appropriately rated, enclosed switching arrangement. Do not connect mains electricity to a breadboard or handle exposed live wiring.

## 🚀 Installation and Setup

The project uses separate Arduino programs for scanning RFID cards and running the main system.

### Step 1: Scan the RFID Card UID

1. Open `RFID_Scanner.ino` in Arduino IDE.
2. Connect the Arduino Uno to your computer.
3. Upload the scanner program.
4. Open the Serial Monitor using `Ctrl + Shift + M`.
5. Place your RFID card near the RC522 reader.
6. Note the UID displayed in the Serial Monitor.

Example UID:

```text
A1 B2 C3 D4
```

### Step 2: Configure the Main Program

1. Open `Main_Project_Code.ino`.
2. Locate the `masterUID` variable.
3. Replace the example UID with your scanned card UID.
4. Enter the UID in hexadecimal format.

Example:

```cpp
byte masterUID[] = {
    0xA1, 0xB2, 0xC3, 0xD4
};
```

5. Save the program.
6. Upload it to the Arduino Uno.

The system is now configured to recognize the specified authorized RFID card, provided the main program implements the corresponding UID verification and card-presence monitoring logic.

## 👥 Multiple RFID Card Support

The system can also be configured to recognize multiple authorized RFID cards.

This is useful for shared environments such as offices, laboratories, and workspaces.

### Configuration

1. Scan each RFID card using `RFID_Scanner.ino`.
2. Record the UID of each card.
3. Open `RFID_Multiple.ino`.
4. Locate the `authorizedCards` array.
5. Add the authorized UIDs.

Example for four-byte UIDs:

```cpp
byte authorizedCards[][4] = {
    {0xA1, 0xB2, 0xC3, 0xD4},  // First Card
    {0xE5, 0xF6, 0x12, 0x34},  // Second Card
    {0x78, 0x90, 0xAB, 0xCD}   // Third Card
};
```

Make sure the program's UID comparison logic supports the UID lengths of the cards being used.

## 📂 Project Structure

```text
Smart-RFID-Power-Saver/
│
├── README.md
│
├── Arduino_Code/
│   ├── RFID_Scanner.ino
│   ├── Main_Project_Code.ino
│   └── RFID_Multiple.ino
│
├── Circuit_Diagram/
│   └── circuit.png
│
├── Documentation/
│   └── Project_Report.pdf
│
├── Images/
│   ├── project_setup.jpg
│   └── circuit_connection.jpg
│
└── Demo/
    └── project_demo.mp4
```

## 🔮 Future Improvements

- Real-time power consumption monitoring.
- Energy usage reports.
- Admin-controlled RFID authorization.
- Improved user management.
- Usage history and analytics.
- Integration with IoT-based monitoring.
- Mobile-based system monitoring.

## 👨‍💻 Team and Contributions

**Project Type:** Semester 3 – Idea Lab Project

This project was developed collaboratively.

| Abhishek Gupta | Original Project Idea and Concept |
| Nitin Chaurasiya | Hardware Components and Physical Implementation |

Additional contributions to programming, testing, and documentation should be credited to the person who performed that work.

## 📚 Learning Outcomes

Through this project, we explored:

- Arduino programming.
- RFID communication.
- SPI protocol.
- Embedded system development.
- Relay-based automation.
- Hardware and software integration.
- Energy management concepts.

## ⚠️ Disclaimer

This project is an academic prototype developed for educational purposes. It should not be used for controlling household mains electricity without appropriate electrical protection, isolation, enclosure, and qualified installation.

## ⭐ Acknowledgement

We acknowledge the collaborative effort involved in developing this project and appreciate the opportunity to explore practical applications of RFID technology and embedded systems.

---

**Developed as a Semester 3 Idea Lab Project.**