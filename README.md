# 🔋 Smart RFID Power Saver (Automatic Cutoff System)

An Arduino-based energy-saving system that uses an RC522 RFID reader and a relay module to automatically cut off electricity when the RFID card is removed.

---

## 🛠️ Hardware Requirements
* **Microcontroller:** Arduino Uno
* **RFID Reader:** RC522 RFID Module
* **Tags:** RFID Card / Key Fob
* **Switching:** 5V Single Channel Relay Module
* Jumper Wires & Breadboard

---

## 💾 Software & Libraries Required

Is project ko compile aur chalane ke liye aapko Arduino IDE me ye libraries chahiye hongi:

1. **SPI Library** *(Inbuilt)*: Yeh Arduino aur RFID reader ke beech communication (SPI protocol) ke liye use hoti hai. Ise alag se install karne ki zaroori nahi hai, yeh Arduino IDE me pehle se aati hai.
2. **MFRC522 Library** *(External)*: RFID Reader (RC522) se data read karne ke liye yeh sabse zaroori library hai.

### 📥 How to install MFRC522 Library:
* Arduino IDE open karein.
* **Sketch** ➡️ **Include Library** ➡️ **Manage Libraries...** par jaayein.
* Search baar me `MFRC522` type karein.
* *Github Community* ya *Rufus Antoniu* wali library ko select karke **Install** par click kar dein.

---

## 🔌 Circuit Connections

### 1. RC522 RFID Reader to Arduino Uno
| RFID Reader Pin | Arduino Uno Pin | Description |
| :--- | :--- | :--- |
| **VCC** | 3.3V | ⚠️ *Do not connect to 5V* |
| **GND** | GND | Ground |
| **RST** | Pin 9 | Reset Pin |
| **SDA** | Pin 10 | SPI SS (Select) |
| **MOSI** | Pin 11 | SPI MOSI |
| **MISO** | Pin 12 | SPI MISO |
| **SCK** | Pin 13 | SPI Clock |
| **IRQ** | *Not Connected* | Khali Chhod Dein |

### 2. Relay Module to Arduino Uno
| Relay Module Pin | Arduino Uno Pin | Description |
| :--- | :--- | :--- |
| **VCC** | 5V | Power Supply |
| **GND** | GND | Ground |
| **IN (Signal)** | Pin 3 | Relay Control Signal |

---

## 🚀 How to Setup and Run (Step-by-Step)

Is project ko chalane ke liye 2 alag-alag codes ka use hota hai. Pehle hume Card ka UID pata karna hota hai, fir use main code me daalna hota hai.

### Step 1: RFID Card ka UID Pata Karein
Sabse pehle aapko check karna hoga ki aapke RFID Card/Tag ka unique number (UID) kya hai.
1. `RFID_Scanner.ino` code ko open karein aur Arduino me upload karein.
2. Arduino IDE ka **Serial Monitor** (`Ctrl + Shift + M`) open karein.
3. Apne RFID card ko reader par tap karein.
4. Serial Monitor par aapko ek code dikhega (Jaise: `A1 B2 C3 D4`). Is code ko kahin copy karke rakh lein.

### Step 2: Main Code Setup Karein
Ab hum main automation code setup karenge.
1. `Main_Project_Code.ino` file ko open karein.
2. Code ke andar jahan `masterUID` daalne ka option hai, wahan Step 1 me copy kiya hua apna card code HEX format me paste kar dein. *(Jaise agar scanner `A1 B2 C3 D4` bataye, toh use code me `{0xA1, 0xB2, 0xC3, 0xD4}` likhein)*.
3. Is main code ko Arduino me upload kar dein.

**Ab aapka system ready hai!** Jaise hi aap wahi card tap karoge, relay ON ho jayega (line active ho jayegi), aur hatate hi bijli turant kat jayegi!
