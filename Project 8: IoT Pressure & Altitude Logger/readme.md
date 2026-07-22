# IoT Pressure & Altitude Logger (Simulation)

## Project Overview

This project demonstrates an IoT-based Pressure & Weather Trend Logger using an ESP32. Since the BMP280 pressure sensor and potentiometer were not available, atmospheric pressure values are simulated while temperature and humidity are measured using a DHT11 sensor.

The system displays environmental data on an OLED display, stores pressure readings in a circular buffer, predicts weather trends based on pressure changes, and indicates the trend using LEDs.

---

## Features

- Simulated Atmospheric Pressure (hPa)
- Real Temperature Monitoring using DHT11
- Real Humidity Monitoring using DHT11
- Circular Buffer (24 Pressure Readings)
- Pressure Trend Detection
  - Rising
  - Falling
  - Stable
- OLED Display (2 Pages)
- Green and Red LED Status Indicators
- Serial Monitor Data Logging

---

## Components Used

| Component | Quantity |
|-----------|----------|
| ESP32 Dev Board | 1 |
| DHT11 Temperature & Humidity Sensor | 1 |
| OLED Display 0.96" SSD1306 | 1 |
| Green LED | 1 |
| Red LED | 1 |
| 220Ω Resistors | 2 |
| Breadboard | 1 |
| Jumper Wires | As Required |

---

## Circuit Connections

### OLED Display

| OLED | ESP32 |
|------|-------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

### DHT11

| DHT11 | ESP32 |
|--------|-------|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO4 |

### LEDs

| LED | ESP32 |
|-----|-------|
| Green LED | GPIO25 |
| Red LED | GPIO26 |

---

## Working Principle

1. ESP32 reads temperature and humidity from the DHT11 sensor.
2. Pressure values are simulated to imitate a BMP280 sensor.
3. Every reading is stored inside a 24-element circular buffer.
4. The newest pressure value is compared with previous values.
5. Weather trend is calculated:
   - Rising Pressure → Good Weather
   - Falling Pressure → Rain Likely
   - Stable Pressure → Normal Weather
6. OLED alternates between:
   - Environmental Data
   - Weather Trend
7. LEDs indicate the current trend:
   - Green → Rising/Stable
   - Red → Falling

---

## Pressure Trend Logic

```
Difference > +0.2 hPa
→ Rising

Difference < -0.2 hPa
→ Falling

Otherwise
→ Stable
```

---

## Circular Buffer

The last 24 pressure readings are stored in an array.

```
pressureLog[24]
```

When the array becomes full, the oldest value is automatically replaced by the newest reading.

---

## OLED Pages

### Page 1

```
Pressure Logger

Pressure : 1013.5 hPa
Temp     : 31.8 C
Humidity : 64%
```

### Page 2

```
Weather Trend

↑ Rising
```

or

```
↓ Falling
```

or

```
→ Stable
```

---

## Serial Monitor Output

```
-------------------------------------
Pressure    : 1014.3 hPa
Temperature : 31.5 C
Humidity    : 62 %
Trend       : RISING
-------------------------------------
```

---

## Sea-Level Pressure Formula

The original BMP280 project uses the following equation to calculate sea-level pressure:

```
P₀ = P / (1 - altitude / 44330)^5.255
```

Where:

- **P₀** = Sea-level pressure
- **P** = Measured atmospheric pressure
- **Altitude** = Height above sea level

Higher altitudes result in lower atmospheric pressure. Converting measured pressure to sea-level pressure allows readings from different locations to be compared accurately.

In this modified project, altitude and pressure are simulated because a BMP280 sensor and potentiometer were unavailable.

---

## Limitations

- No BMP280 sensor available.
- Pressure values are simulated.
- Altitude is not measured.
- Sea-level pressure is demonstrated conceptually.

---

## Future Improvements

- Replace simulated pressure with a BMP280 sensor.
- Add altitude compensation using a potentiometer.
- Store readings on an SD card.
- Publish readings using MQTT.
- Display pressure graphs on a web dashboard.
- Add Wi-Fi-based remote monitoring.

---

## Folder Structure

```
p8-pressure-logger/
│
├── Pressure_Logger_Simulator.ino
├── README.md


---

## Author

**Shobhit Singh**


ESP32 IoT Summer Training Project

2026
