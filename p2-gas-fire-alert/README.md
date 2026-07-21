# Project 2: Gas & Fire Safety Alert System

## Overview

The Gas & Fire Safety Alert System is an Arduino-based safety project designed to detect gas leaks and fire hazards. It continuously monitors gas concentration using an MQ-2 gas sensor and detects fire using a flame sensor (simulated in Wokwi with a slide switch). According to the detected condition, the system activates LEDs and buzzers to alert the user.

---

## Features

- Gas leakage detection using MQ-2 sensor
- Flame detection (active-low simulation)
- Three safety levels:
  - Safe
  - Warning
  - Danger
- Independent gas and flame alerts
- Dual active buzzers
- Three LED indicators
- Serial Monitor status logging every second

---

## Components Used

- Arduino Uno R3
- MQ-2 Gas Sensor
- Slide Switch (Simulated Flame Sensor)
- 2 Active Buzzers
- Green LED
- Yellow LED
- Red LED
- 3 × 220Ω Resistors
- Breadboard
- Jumper Wires

---

## Circuit Connections

| Component | Arduino Pin |
|-----------|-------------|
| MQ-2 AO | A0 |
| MQ-2 VCC | 5V |
| MQ-2 GND | GND |
| Flame Sensor (Slide Switch) | D7 |
| Gas Buzzer | D8 |
| Fire Buzzer | D9 |
| Green LED | D10 |
| Yellow LED | D11 |
| Red LED | D12 |

---

## Working

### Safe
- Gas level below 30%
- Green LED ON
- Buzzers OFF

### Warning
- Gas level between 30% and 60%
- Yellow LED ON
- Gas buzzer beeps once every second

### Gas Danger
- Gas level above 60%
- Red LED ON
- Gas buzzer continuously ON

### Fire Danger
- Flame detected
- Red LED ON
- Fire buzzer activated

### Gas + Fire Danger
- Gas above 60% and flame detected
- Red LED ON
- Both buzzers activated

---

## Serial Monitor Example

```
Gas & Fire Alert System
System Ready

Gas = 20% | Flame = NO | Status = SAFE
Gas = 45% | Flame = NO | Status = WARNING
Gas = 84% | Flame = NO | Status = GAS DANGER
Gas = 20% | Flame = YES | Status = FIRE DANGER
Gas = 90% | Flame = YES | Status = GAS + FIRE
```

---

## Wokwi Simulation Note

Wokwi does not currently provide a flame sensor component. A slide switch was used to simulate the flame sensor's active-low digital output while keeping the project logic identical to a real flame sensor.

---

## Folder Structure

```
p2-gas-fire-alert/
│── Gas_Fire_Alert.ino
│── README.md
│── wokwi-project.json
│── diagram.json
│── images/
│     ├── circuit.png
│     ├── safe.png
│     ├── warning.png
│     ├── gas-danger.png
│     ├── fire-danger.png
│     ├── gas-fire-danger.png
│── demo.mp4
```

---

## Technologies Used

- Arduino IDE
- Embedded C++
- Wokwi Simulator

---

## Learning Outcomes

- Analog sensor interfacing
- Digital sensor interfacing
- Threshold-based decision making
- Active-low sensor logic
- LED and buzzer control
- Safety monitoring systems
- Arduino programming

---

## Author

**Shobhit Singh**

Summer School 2026  

IIT Jammu × Techible × I3C IIT Jammu
