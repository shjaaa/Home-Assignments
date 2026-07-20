🚗 Ultrasonic Parking Assistant

This project is an ESP32-based parking assistant that measures the distance between the vehicle and an obstacle using an HC-SR04 ultrasonic sensor. Based on the measured distance, LEDs and a buzzer provide visual and audio feedback while an OLED displays the current distance and parking zone.

Components
ESP32 Dev Board
HC-SR04 Ultrasonic Sensor
OLED SSD1306 Display
Active Buzzer
Blue LED
Yellow LED
Red LED
Breadboard & Jumper Wires
Features
Real-time distance measurement
Average of 5 sensor readings
OLED display with distance and parking zone
Proximity bar graph
Four parking safety zones
Audio and visual alerts
Serial Monitor logging
Distance Formula

The HC-SR04 measures the time taken for an ultrasonic pulse to travel to an object and back.

Distance = (Duration × 0.0343) / 2

where:

Duration = Echo pulse time (µs)
0.0343 = Speed of sound (cm/µs)
Division by 2 accounts for the round trip.
Parking Zones
Distance	Zone
>60 cm	SAFE
30–60 cm	CAUTION
15–30 cm	CLOSE
<15 cm	DANGER
Technologies
ESP32
Arduino IDE
Embedded C++
HC-SR04
OLED SSD1306
