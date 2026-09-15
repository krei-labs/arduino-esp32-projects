<h1 align="center">Arduino Projects</h1>

<p align="center">
  Academic, embedded-systems, sensor, automation, display, and creative projects built on Arduino-compatible boards.
</p>

<p align="center">
  <img alt="Arduino" src="https://img.shields.io/badge/Arduino-C%2FC%2B%2B-00979d?logo=arduino&logoColor=white">
  <img alt="Projects" src="https://img.shields.io/badge/Projects-16-blue">
</p>

---

⬅ Back to the [main repository](../README.md).

A collection of Arduino-based projects developed during my Computer Engineering studies, progressing from basic digital I/O and single sensors toward multi-component automation and display-driven interfaces.

## 📑 Projects

<div align="center">

| # | Project | Main Concepts |
|:---:|---|---|
| 01 | [DHT11 Temperature Serial Monitor](01-dht11-temperature-serial-monitor) | DHT11, Serial |
| 02 | [DHT11 LCD Temperature Monitor](02-dht11-lcd-temperature-alarm) | DHT11, LCD, buzzer |
| 03 | [IR Sensor LED Detector](03-ir-led-detector) | Digital input/output |
| 04 | [Serial LED Blinker](04-serial-led-blinker) | Timing, Serial |
| 05 | [Ultrasonic Radar Scanner](05-ultrasonic-radar-lcd) | Servo, ultrasonic, LCD |
| 06 | [Ultrasonic Radar Scanner + Debug](06-ultrasonic-radar-lcd-serial-debug) | Servo, ultrasonic, Serial |
| 07 | [Smart Parking Gate](07-smart-parking-gate-counter) | IR, ultrasonic, servo, LCD |
| 08 | [Traffic Light and Vehicle Gate](08-traffic-light-vehicle-gate) | Ultrasonic, servo, LEDs |
| 09 | [Automatic Dual-Servo Bin](09-dual-servo-automatic-bin) | Ultrasonic, servos |
| 10 | [Smart Room Occupancy System](10-smart-room-occupancy-system) | IR, ultrasonic, DHT11, servo, alarm |
| 11 | [OLED Bitmap Animation](11-oled-bitmap-animation-48x48) | SSD1306, bitmap frames |
| 12 | [OLED Emotion Eyes](12-oled-emotion-eyes) | SH1106, animation |
| 13 | [OLED Story Animation](13-oled-bitmap-story-animation) | SH1106, bitmap frames |
| 14 | [LCD Servo and LED Music Display](14-lcd-servo-led-music-display) | LCD, servo, LED |
| 15 | [LCD Timed Text Display](15-lcd-lyrics-display) | LCD, timing |
| 16 | [LCD Greeting Display](16-lcd-teachers-day-greeting) | LCD, I2C |

</div>

## 🛠️ Libraries Used Across These Projects

`DHT sensor library` · `LiquidCrystal_I2C` · `Servo` · `Adafruit GFX` · `Adafruit SSD1306` · `Adafruit SH110X`

## 🎯 Purpose

These projects document my progression from basic Arduino input/output and single sensors toward integrated embedded systems — combining sensors, displays, actuators, and timing/state logic into increasingly complete automation and interface projects.

## ▶️ Running Any Project Here

1. Open a project folder and check its `README.md` for the specific hardware and libraries.
2. Open the `.ino` file in the Arduino IDE.
3. Install the required libraries via the Library Manager.
4. Select your Arduino-compatible board and serial port.
5. Wire the hardware per the pin definitions in the source code, then upload.

> **Hardware warning:** Pin assignments and power requirements should be verified before wiring. Servos, motors, and other loads may need an external power supply and shared ground.

---

<p align="center"><strong>Christian G. Maranan</strong> — kréi / Krei Labs — <a href="https://github.com/krei-labs">@krei-labs</a></p>
