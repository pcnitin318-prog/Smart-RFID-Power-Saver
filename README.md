# Smart-RFID-Power-Saver
An Arduino-based energy-saving system that uses an RC522 RFID reader and a relay module to automatically cut off electricity when the RFID card is removed.

## 🚀 How to Setup and Run (Step-by-Step)

Is project ko chalane ke liye 2 alag-alag codes ka use hota hai. Pehle hume Card ka UID pata karna hota hai, fir use main code me daalna hota hai.

### Step 1: RFID Card ka UID Pata Karein
Sabse pehle aapko check karna hoga ki aapke RFID Card/Tag ka unique number (UID) kya hai.
1. `RFID_Scanner.ino` code ko open karein aur Arduino me upload karein.
2. Arduino IDE ka **Serial Monitor** (Ctrl+Shift+M) open karein.
3. Apne RFID card ko reader par tap karein.
4. Serial Monitor par aapko ek code dikhega (Jaise: `A1 B2 C3 D4`). Is code ko kahin copy karke rakh lein.

### Step 2: Main Code Setup Karein
Ab hum main automation code setup karenge.
1. `Main_Project_Code.ino` file ko open karein.
2. Code ke andar jahan `masterCardUID` ya card number daalne ka option hai, wahan Step 1 me copy kiya hua apna code paste kar dein.
3. Is main code ko Arduino me upload kar dein.

Ab aapka system ready hai! Jaise hi aap wahi card tap karoge, relay ON ho jayega, aur hatate hi bijli kat jayegi.


## 🛠️ Hardware Requirements
* Arduino Uno
* RC522 RFID Reader
* RFID Card / Tag
* 5V Single Channel Relay Module
* Jumper Wires & Breadboard

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
* **VCC** ➡️ Arduino 5V
* **GND** ➡️ Arduino GND
* **IN (Signal)** ➡️ Arduino Pin 3

---

Ab aapka system ready hai! Card tap hone par appliance chalega, hatate hi band!
