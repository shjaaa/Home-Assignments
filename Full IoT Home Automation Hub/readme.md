# 🏠 Full IoT Home Automation Hub using ESP32

The **IoT Home Automation Hub using ESP32** is a smart room automation system designed to monitor environmental conditions and automatically control appliances using IoT technology. This project combines sensor interfacing, relay automation, OLED display, Wi-Fi communication, web dashboard monitoring, and MQTT-based data publishing into a single system. The main controller used in this project is an ESP32 development board, which collects real-time data from a DHT11 temperature and humidity sensor and an LDR light sensor. Based on the sensor readings, the system automatically controls a fan and light using relay modules. The fan automation works using temperature-based control where the fan turns ON when the temperature rises above 32°C and turns OFF when the temperature falls below 28°C using hysteresis logic to avoid frequent switching. The light automation works using the LDR sensor where the light turns ON during low light conditions and turns OFF when sufficient brightness is detected. The system also provides manual control using push buttons, allowing users to override automatic operation when required. Real-time sensor values and appliance status are displayed on a 0.96-inch I2C OLED display, which shows temperature, humidity, light intensity, relay status, and system uptime. The ESP32 creates a web-based dashboard that allows users to monitor sensor readings and control appliances remotely through a browser connected to the same Wi-Fi network. The project also uses MQTT communication to publish sensor data to the HiveMQ public broker using the topic `iitjammu/[yourname]/home`, allowing IoT devices and monitoring applications to access live system information. The MQTT messages are transmitted in JSON format containing parameters such as temperature, humidity, LDR value, fan status, light status, and uptime. The system tracks uptime using the ESP32 `millis()` function and displays the running time on both the OLED display and web dashboard. The hardware components used include ESP32 Dev Board, DHT11 temperature and humidity sensor, LDR sensor with 10kΩ resistor, relay module, OLED display, push buttons, breadboard, and jumper wires. The software environment includes Arduino IDE, ESP32 board support package, PubSubClient library for MQTT communication, Adafruit SSD1306 and GFX libraries for OLED display, and ESPAsyncWebServer library for creating the web dashboard. The project demonstrates how ESP32 can be used to build a complete IoT-based home automation solution by integrating sensors, actuators, wireless communication, and real-time monitoring. Future improvements include adding MQ-2 gas detection, PIR-based motion sensing, mobile application support, cloud data storage, voice assistant integration, and AI-based energy optimization. **Note: This implementation does not include PIR motion sensor and MQ-2 gas sensor features.**

## Hardware Components Used
- ESP32 Development Board
- DHT11 Temperature and Humidity Sensor
- LDR Sensor + 10kΩ Resistor
- Relay Module
- 0.96" OLED I2C Display
- Push Buttons
- Breadboard and Jumper Wires

## Pin Configuration
- DHT11 Data → GPIO4
- LDR Sensor → GPIO34
- Fan Relay → GPIO26
- Light Relay → GPIO27
- OLED SDA → GPIO21
- OLED SCL → GPIO22
- Fan Button → GPIO0
- Light Button → GPIO32

## MQTT Configuration
Broker:
`broker.hivemq.com'
