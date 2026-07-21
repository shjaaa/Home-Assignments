# Stepper Motor Precision Positioner (Servo Version)

## Hardware
- ESP32
- SG90 Servo Motor
- OLED Display (SSD1306)
- 3 Push Buttons
- LED
- Breadboard
- Jumper Wires

## Features
- Clockwise rotation (+45°)
- Counter-clockwise rotation (-45°)
- Home position button
- OLED shows:
  - Current Angle
  - Direction
  - Simulated Steps
- LED flashes on movement
- Serial Monitor logs every movement

## Note

The original assignment required a 28BYJ-48 Stepper Motor with ULN2003 driver.

Since those components were unavailable, this implementation uses an SG90 Servo Motor while preserving the same control logic (CW, CCW, Home, Position Tracking, OLED Display).
