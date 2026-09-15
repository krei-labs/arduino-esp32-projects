# ESP32 Environmental Monitoring and Control Hub

**Platform:** ESP32

## Overview

A Wi-Fi access-point-based environmental hub that reads temperature/humidity, air quality, light, and soil moisture, controls a pump/fan/LED, logs readings, and exposes a local web interface with JSON endpoints.

## Hardware

- ESP32
- DHT11
- MQ135
- LDR
- Soil-moisture sensor
- Relays
- Pump
- Fan
- LED
- 16x4 I2C LCD

## Libraries

- `DHT sensor library`
- `LiquidCrystal_I2C`
- `ArduinoJson`

## How It Works

The sketch initializes the connected hardware in `setup()` and runs the project logic from `loop()`. The implementation is intentionally kept close to the original project so the repository reflects the actual work and learning progression.

## Main Concepts Demonstrated

- Digital input/output
- Sensor reading and threshold-based decisions
- Actuator control
- Timing and sequencing
- Embedded-system logic
- Serial debugging where applicable

## Notes

The original code contained a Wi-Fi password. The GitHub-ready copy replaces it with `CHANGE_ME_123` so credentials are not published.

## Running the Project

1. Open the `.ino` file in Arduino IDE.
2. Select the appropriate board and COM/serial port.
3. Install the libraries listed above.
4. Connect the hardware according to the pin definitions in the source code.
5. Upload the sketch.
6. Test the system and monitor Serial output when available.

> **Hardware warning:** Pin assignments and power requirements should be verified before wiring. Servos, motors, relays, and other loads may require an appropriate external power supply and common ground.

## Project History

This is an academic/personal project that was originally developed earlier and later organized, renamed, and documented for my GitHub portfolio. The GitHub upload date reflects the date it was published or revisited, not necessarily the original development date.

---

**Developer:** Christian G. Maranan  
**GitHub:** `krei-labs`  
**Brand:** **kréi — Krei Labs**
