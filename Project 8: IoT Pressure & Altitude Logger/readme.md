IoT Pressure & Altitude Logger using ESP32
Overview

This project implements an IoT Pressure & Altitude Logger using an ESP32, BMP180 pressure sensor (used in place of BMP280 for simulation), OLED display, potentiometer, and LEDs. The system continuously measures atmospheric pressure and temperature, simulates local altitude using a potentiometer, calculates sea-level pressure, stores the last 24 pressure readings in a circular buffer, determines the weather trend (RISING, FALLING, or STABLE), and displays the information on a 0.96" OLED display. The OLED alternates between sensor readings and weather trend every 5 seconds. The project also provides real-time monitoring through the Serial Monitor and visual status indication using LEDs.

Features
Atmospheric pressure measurement using BMP180
Temperature monitoring
Altitude simulation using a potentiometer (0–2000 m)
Sea-level pressure calculation
Circular buffer storing the last 24 pressure readings
Weather trend detection (RISING, FALLING, STABLE)
Automatic OLED page switching every 5 seconds
Green LED for Rising/Stable trend
Red LED for Falling trend
Serial Monitor output every 30 seconds
I2C communication between ESP32, BMP180, and OLED
Components Used
ESP32 DevKit V1
BMP180 Pressure Sensor (BMP280 substituted with BMP180 in Wokwi)
OLED Display 0.96" SSD1306 (I2C)
10kΩ Potentiometer
Green LED
Red LED
220Ω Resistors ×2
Breadboard
Jumper Wires
Circuit Connections
BMP180
BMP180 Pin	ESP32 Pin
VCC	3.3V
GND	GND
SDA	GPIO21
SCL	GPIO22
OLED Display
OLED Pin	ESP32 Pin
VCC	3.3V
GND	GND
SDA	GPIO21
SCL	GPIO22
Potentiometer
Potentiometer	ESP32
VCC	3.3V
GND	GND
SIG	GPIO34
LEDs
Component	ESP32 Pin
Green LED	GPIO25
Red LED	GPIO26
Working Principle
The ESP32 reads pressure and temperature from the BMP180 sensor every 30 seconds.
The potentiometer is used to simulate local altitude between 0 and 2000 meters.
Sea-level pressure is calculated using the standard atmospheric formula.
Each pressure reading is stored in a circular buffer containing the latest 24 readings.
The newest pressure is compared with the oldest stored reading to determine the weather trend:
Rising
Falling
Stable
The OLED alternates every 5 seconds between:
Pressure, Temperature and Altitude
Weather Trend
LEDs indicate the current weather trend.
All sensor readings are printed to the Serial Monitor.
Pressure Trend Logic
Pressure Difference	Trend
Greater than +0.5 hPa	RISING
Less than -0.5 hPa	FALLING
Between -0.5 and +0.5 hPa	STABLE
Sea-Level Pressure Formula

The sea-level pressure is calculated using the standard atmospheric equation:

P₀ = P / (1 - h / 44330) ^ 5.255

Where:

P₀ = Sea-level pressure (hPa)
P = Measured pressure (hPa)
h = Altitude (meters)

This compensates for altitude differences and allows pressure readings from different locations to be compared.

OLED Display
Screen 1
Pressure (hPa)
Temperature (°C)
Altitude (m)
Screen 2
Weather Trend
↑ Rising
↓ Falling
→ Stable

The display automatically switches between both screens every 5 seconds.

Serial Monitor Output
--------------------------------------
Pressure      : 1008.45 hPa
Temperature   : 28.6 °C
Altitude      : 850 m
Sea Level Pressure : 1116.32 hPa
Trend         : RISING
--------------------------------------
Project Structure
p8-pressure-logger/
│── sketch.ino
│── README.md
Wokwi Simulation

This project was simulated using Wokwi. Since BMP280 was unavailable in Wokwi, the BMP180 sensor was used as a compatible alternative. The potentiometer simulates local altitude for demonstrating sea-level pressure compensation and trend analysis.

Future Improvements
MQTT publishing to HiveMQ
SD card data logging
Cloud dashboard integration
Pressure graph visualization
Weather forecast based on long-term pressure trends
Web dashboard using ESP32 Wi-Fi
Author

Shobhit Singh
Jaypee Institute of Information Technology (JIIT), Noida
ECE Department
Summer School 2026 – IIT Jammu IoT Home Assignments
