# Project 1: Smart Room Climate Monitor

## IIT Jammu Summer School 2026

### Objective

Build a Smart Room Climate Monitor using ESP32 that measures temperature and humidity using a DHT11 sensor. The readings are displayed on an OLED display, while LEDs and a buzzer indicate the room condition.

---

## Components Used

- ESP32 Dev Board
- DHT11 Temperature & Humidity Sensor
- OLED Display (SSD1306 0.96")
- Active Buzzer
- Red LED
- Green LED
- 220Ω Resistors
- Breadboard
- Jumper Wires

---

## Circuit Connections

### DHT11

- VCC → 3.3V
- GND → GND
- DATA → GPIO4

### OLED

- VCC → 3.3V
- GND → GND
- SDA → GPIO21
- SCL → GPIO22

### LEDs

Green LED

- GPIO26 → 220Ω → LED → GND

Red LED

- GPIO25 → 220Ω → LED → GND

### Buzzer

- Signal → GPIO27
- VCC → 3.3V
- GND → GND

---

## Libraries Used

- DHTesp
- Adafruit GFX
- Adafruit SSD1306

---

## Features

- Reads temperature every 2 seconds
- Reads humidity every 2 seconds
- Displays values on OLED
- Green LED indicates normal conditions
- Red LED and buzzer activate during danger conditions
- Serial Monitor outputs CSV data
- Displays status:
  - COOL
  - COMFORT
  - HOT
  - DANGER

---

## Expected Output

OLED

Temperature: 29°C

Humidity: 60%

Status: COMFORT

Serial Monitor

5000,29.2,60,COMFORT

10000,30.1,61,COMFORT

15000,39.4,82,DANGER

---

## How to Run

1. Connect all components.
2. Install the required libraries.
3. Select ESP32 Dev Module.
4. Upload the code.
5. Open Serial Monitor at 115200 baud.
6. Observe the OLED display and LEDs.

---

## Author

Shobhit Singh
JIIT Noida
ECE
Summer School 2026 – IIT Jammu
