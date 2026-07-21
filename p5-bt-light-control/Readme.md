# Project 5: Bluetooth Home Light Controller

## Overview
This project implements a Bluetooth-based home light controller using the ESP32. Two relay channels simulate home lights and can be controlled wirelessly from an Android phone using Bluetooth Classic (SPP). A manual push button is also provided for local control.

## Features
- ESP32 Bluetooth Classic (SPP)
- Bluetooth device name: IIT_IoT_HomeCtrl
- Control two lights using Bluetooth
- Manual push-button control
- Relay switching
- LED status indication
- Confirmation buzzer
- Automatic light OFF after 30 minutes of inactivity
- Status response for every command

---

## Components Used

- ESP32 Dev Board
- 2-Channel Relay Module
- 2 LEDs
- 220Ω Resistors
- KY-004 Push Button Module (1 Button)
- Active Buzzer
- Breadboard
- Jumper Wires

---

## Circuit Connections

| Component | ESP32 Pin |
|----------|-----------|
| Relay IN1 | GPIO26 |
| Relay IN2 | GPIO27 |
| LED 1 | GPIO25 |
| LED 2 | GPIO33 |
| Push Button | GPIO13 |
| Buzzer | GPIO32 |
| Built-in LED | GPIO2 |

---

## Bluetooth Commands

| Command | Function |
|---------|----------|
| 1 | Light 1 ON |
| 2 | Light 1 OFF |
| 3 | Light 2 ON |
| 4 | Light 2 OFF |
| 5 | Both Lights ON |
| 6 | Both Lights OFF |
| ? | Display Current Status |

Example Response

L1:ON L2:OFF

---

## Working

1. Power ON the ESP32.
2. Pair your Android phone with **IIT_IoT_HomeCtrl**.
3. Open the Serial Bluetooth Terminal app.
4. Send the supported commands.
5. The ESP32 switches the corresponding relay and LED.
6. The buzzer gives a confirmation beep.
7. The current light status is sent back to the phone.
8. The manual push button toggles both lights simultaneously.
9. If no Bluetooth command is received for 30 minutes, all lights are switched OFF automatically.

---


## Technologies Used

- Arduino IDE
- ESP32
- BluetoothSerial Library
- Embedded C++

---

## Learning Outcomes

- Bluetooth communication using ESP32
- Serial Port Profile (SPP)
- Relay interfacing
- GPIO control
- Manual override implementation
- State management
- Embedded system programming

---

## Author

**Shobhit Singh**

Summer School 2026

IIT Jammu × Techible × I3C IIT Jammu
