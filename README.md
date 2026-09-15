<h1 align="center">Arduino & ESP32 Embedded Projects</h1>

<p align="center">
  A curated collection of Arduino and ESP32 projects spanning sensors, displays, robotics, wireless control, and embedded web systems.
</p>

<p align="center">
  <img alt="Arduino" src="https://img.shields.io/badge/Arduino-C%2FC%2B%2B-00979d?logo=arduino&logoColor=white">
  <img alt="ESP32" src="https://img.shields.io/badge/ESP32-Wi--Fi%20%2F%20Bluetooth-e7352c?logo=espressif&logoColor=white">
  <img alt="Projects" src="https://img.shields.io/badge/Projects-22-blue">
  <img alt="License" src="https://img.shields.io/badge/License-Academic%20Portfolio-lightgrey">
</p>

---

This repository documents my progression through Computer Engineering coursework — from **basic electronics and sensor exercises** to **robotics, wireless control, OLED interfaces, automation, and an ESP32 environmental monitoring hub**. Every folder is a self-contained sketch with its own README, hardware list, and library requirements.

> **Portfolio note:** Some projects were originally created earlier in college and later revisited for GitHub. Folder/file names and documentation were cleaned up to make the work easier to understand. The GitHub publication date should not be interpreted as the original development date.

---

## 📑 Table of Contents

- [Repository Structure](#-repository-structure)
- [Arduino Projects](#-arduino-projects)
- [ESP32 Projects](#-esp32-projects)
- [Technology Areas](#%EF%B8%8F-technology-areas)
- [Development Progression](#-development-progression)
- [Skills Demonstrated](#-skills-demonstrated)
- [Running a Project](#%EF%B8%8F-running-a-project)
- [GitHub Safety](#-github-safety)
- [Hardware Disclaimer](#%EF%B8%8F-hardware-disclaimer)
- [Future Improvements](#-future-improvements)
- [License](#-license)
- [Author](#-author)

---

## 📂 Repository Structure

```text
arduino-esp32-projects/
│
├── arduino/                     # 16 Arduino sketches — see arduino/README.md
│   ├── 01-dht11-temperature-serial-monitor/
│   ├── 02-dht11-lcd-temperature-alarm/
│   ├── 03-ir-led-detector/
│   ├── 04-serial-led-blinker/
│   ├── 05-ultrasonic-radar-lcd/
│   ├── 06-ultrasonic-radar-lcd-serial-debug/
│   ├── 07-smart-parking-gate-counter/
│   ├── 08-traffic-light-vehicle-gate/
│   ├── 09-dual-servo-automatic-bin/
│   ├── 10-smart-room-occupancy-system/
│   ├── 11-oled-bitmap-animation-48x48/
│   ├── 12-oled-emotion-eyes/
│   ├── 13-oled-bitmap-story-animation/
│   ├── 14-lcd-servo-led-music-display/
│   ├── 15-lcd-lyrics-display/
│   └── 16-lcd-teachers-day-greeting/
│
└── esp32/                       # 6 ESP32 sketches — see esp32/README.md
    ├── 01-bluetooth-rc-car-servo-controller/
    ├── 02-bluetooth-sumo-car-servo-controller/
    ├── 03-basic-ultrasonic-obstacle-avoidance/
    ├── 04-smart-ultrasonic-scanning-robot/
    ├── 05-autonomous-path-driving-robot/
    └── 06-environmental-monitoring-hub/
```

Each project folder contains:

- `README.md` — project-specific overview, hardware list, libraries, and run steps
- `<project-name>.ino` — Arduino/ESP32 source code

---

## 🔩 Arduino Projects

<div align="center">

| # | Project | Main Concepts |
|:---:|---|---|
| 01 | [DHT11 Temperature Serial Monitor](arduino/01-dht11-temperature-serial-monitor) | DHT11, Serial |
| 02 | [DHT11 LCD Temperature Monitor](arduino/02-dht11-lcd-temperature-alarm) | DHT11, LCD, buzzer |
| 03 | [IR Sensor LED Detector](arduino/03-ir-led-detector) | Digital input/output |
| 04 | [Serial LED Blinker](arduino/04-serial-led-blinker) | Timing, Serial |
| 05 | [Ultrasonic Radar Scanner](arduino/05-ultrasonic-radar-lcd) | Servo, ultrasonic, LCD |
| 06 | [Ultrasonic Radar Scanner + Debug](arduino/06-ultrasonic-radar-lcd-serial-debug) | Servo, ultrasonic, Serial |
| 07 | [Smart Parking Gate](arduino/07-smart-parking-gate-counter) | IR, ultrasonic, servo, LCD |
| 08 | [Traffic Light and Vehicle Gate](arduino/08-traffic-light-vehicle-gate) | Ultrasonic, servo, LEDs |
| 09 | [Automatic Dual-Servo Bin](arduino/09-dual-servo-automatic-bin) | Ultrasonic, servos |
| 10 | [Smart Room Occupancy System](arduino/10-smart-room-occupancy-system) | IR, ultrasonic, DHT11, servo, alarm |
| 11 | [OLED Bitmap Animation](arduino/11-oled-bitmap-animation-48x48) | SSD1306, bitmap frames |
| 12 | [OLED Emotion Eyes](arduino/12-oled-emotion-eyes) | SH1106, animation |
| 13 | [OLED Story Animation](arduino/13-oled-bitmap-story-animation) | SH1106, bitmap frames |
| 14 | [LCD Servo and LED Music Display](arduino/14-lcd-servo-led-music-display) | LCD, servo, LED |
| 15 | [LCD Timed Text Display](arduino/15-lcd-lyrics-display) | LCD, timing |
| 16 | [LCD Greeting Display](arduino/16-lcd-teachers-day-greeting) | LCD, I2C |

</div>

Full details in [`arduino/README.md`](arduino/README.md).

---

## 📡 ESP32 Projects

<div align="center">

| # | Project | Main Concepts |
|:---:|---|---|
| 01 | [Bluetooth RC Car with Servo Controls](esp32/01-bluetooth-rc-car-servo-controller) | Bluetooth, motors, servos |
| 02 | [Bluetooth Sumo Car with Dual Servos](esp32/02-bluetooth-sumo-car-servo-controller) | Bluetooth, motors, servos |
| 03 | [Ultrasonic Obstacle Avoidance Robot](esp32/03-basic-ultrasonic-obstacle-avoidance) | Ultrasonic, motor control |
| 04 | [Smart Ultrasonic Scanning Robot](esp32/04-smart-ultrasonic-scanning-robot) | Servo scanning, obstacle avoidance |
| 05 | [Autonomous Path-Driving Robot](esp32/05-autonomous-path-driving-robot) | Motor sequencing |
| 06 | [Environmental Monitoring and Control Hub](esp32/06-environmental-monitoring-hub) | Wi-Fi AP, sensors, web dashboard, JSON, relays |

</div>

Full details in [`esp32/README.md`](esp32/README.md).

---

## 🛠️ Technology Areas

<div align="center">

| Category | Arduino | ESP32 |
|:---:|:---:|:---:|
| **Sensors** | DHT11, HC-SR04 ultrasonic, IR | HC-SR04 ultrasonic, DHT11, MQ135, LDR, soil moisture |
| **Actuators** | Servo, DC motor, buzzer, LEDs | Servo (`ESP32Servo`), DC motors, relays, pump, fan |
| **Displays** | 16x2 / 16x4 I2C LCD, SSD1306, SH1106 OLED | 16x4 I2C LCD |
| **Communication** | Serial, I2C | Bluetooth Serial, Wi-Fi (access point), Serial |
| **Web/Data** | — | Embedded HTTP server, JSON responses (`ArduinoJson`) |
| **Storage** | — | EEPROM-backed settings |
| **Core Logic** | Digital I/O, timing/state machines, threshold logic | Motor sequencing, obstacle avoidance, sensor fusion |

</div>

---

## 📈 Development Progression

**Basic I/O → Sensors → Displays → Actuators → Automation → Robotics → Wireless Control → Embedded Web Systems**

These projects aren't presented as isolated code samples — together they trace how hardware components, programming logic, and communication technologies were gradually combined into larger systems, from a single DHT11 serial print to a Wi-Fi-connected environmental hub with a live dashboard.

---

## 🧠 Skills Demonstrated

- Embedded C/C++ programming (Arduino & ESP32)
- Sensor integration and threshold-based decision logic
- Actuator, motor, and servo control
- I2C communication and OLED graphics
- Serial debugging
- Bluetooth communication
- Wi-Fi networking and embedded web-server development
- JSON data handling (`ArduinoJson`)
- Hardware/software integration
- Troubleshooting and iterative development

---

## ▶️ Running a Project

1. Open the desired project folder and read its `README.md` for the hardware list and libraries.
2. Open the `.ino` file in the Arduino IDE (or PlatformIO).
3. Install the listed libraries via the Library Manager.
4. Select the correct board and COM/serial port:
   - Arduino projects → your Arduino-compatible board
   - ESP32 projects → the appropriate ESP32 dev board profile
5. Wire the hardware according to the pin definitions in the source code.
6. Upload the sketch and monitor Serial output where applicable.

---

## 🔐 GitHub Safety

Before publishing embedded projects, always check for:

- Wi-Fi passwords
- API keys
- Tokens
- Personal credentials
- Private client information
- Private network details

The [Environmental Monitoring Hub](esp32/06-environmental-monitoring-hub) has been prepared with a placeholder Wi-Fi password (`CHANGE_ME_123`) instead of the original value.

---

## ⚠️ Hardware Disclaimer

These projects are educational prototypes. Pin assignments, voltage levels, current requirements, motor-driver wiring, relay wiring, and power supplies should be verified before building or modifying the circuits.

---

## 📈 Future Improvements

- Add wiring diagrams / Fritzing schematics per project
- Consolidate shared libraries (Servo, LCD, OLED) into a common reference doc
- Add PlatformIO configs alongside the `.ino` sketches
- Expand the ESP32 web dashboard (hub project) with persistent logging
- Short demo clips or photos for the robotics projects

---

## 📄 License

This repository is a personal/academic portfolio. If you intend to reuse, modify, or redistribute any project, please contact the author first.

---

## 👨‍💻 Author

**Christian G. Maranan**
Computer Engineering Student — Software Development | AI/ML

**kréi — Krei Labs**

- **GitHub:** [@krei-labs](https://github.com/krei-labs)

---

<p align="center"><strong>Build. Learn. Experiment.</strong> — kréi / Krei Labs</p>
