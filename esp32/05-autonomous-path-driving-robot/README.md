# ESP32 Autonomous Path-Driving Robot

**Platform:** ESP32

## Overview

A motor-control exercise that executes a programmed sequence of forward, left, right, and stop movements to follow a predefined path.

## Hardware

- ESP32
- Motor driver
- DC motors

## Libraries

- No external library beyond the standard Arduino environment is explicitly included.

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

Although the original folder was named `WiFiAccessPoint`, the supplied sketch does not initialize Wi-Fi; it only performs a hard-coded movement sequence.

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
