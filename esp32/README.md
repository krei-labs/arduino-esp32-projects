<h1 align="center">ESP32 Projects</h1>

<p align="center">
  Robotics, Bluetooth control, obstacle avoidance, autonomous movement, and environmental monitoring built on the ESP32.
</p>

<p align="center">
  <img alt="ESP32" src="https://img.shields.io/badge/ESP32-Wi--Fi%20%2F%20Bluetooth-e7352c?logo=espressif&logoColor=white">
  <img alt="Projects" src="https://img.shields.io/badge/Projects-6-blue">
</p>

---

⬅ Back to the [main repository](../README.md).

A collection of ESP32-based projects that build on the Arduino fundamentals with wireless control, motor-driven robotics, and an embedded Wi-Fi web interface.

## 📑 Projects

<div align="center">

| # | Project | Main Concepts |
|:---:|---|---|
| 01 | [Bluetooth RC Car with Servo Controls](01-bluetooth-rc-car-servo-controller) | Bluetooth, motors, servos |
| 02 | [Bluetooth Sumo Car with Dual Servos](02-bluetooth-sumo-car-servo-controller) | Bluetooth, motors, servos |
| 03 | [Ultrasonic Obstacle Avoidance Robot](03-basic-ultrasonic-obstacle-avoidance) | Ultrasonic, motor control |
| 04 | [Smart Ultrasonic Scanning Robot](04-smart-ultrasonic-scanning-robot) | Servo scanning, obstacle avoidance |
| 05 | [Autonomous Path-Driving Robot](05-autonomous-path-driving-robot) | Motor sequencing |
| 06 | [Environmental Monitoring and Control Hub](06-environmental-monitoring-hub) | Wi-Fi AP, sensors, web dashboard, JSON, relays |

</div>

## 🛠️ Libraries Used Across These Projects

`ESP32Servo` · `BluetoothSerial` · `DHT sensor library` · `LiquidCrystal_I2C` · `ArduinoJson`

## 🎯 Purpose

These projects show my progression into ESP32 development — wireless control, robotics, sensor fusion, and embedded web interfaces — building on the sensor/actuator fundamentals from the [Arduino projects](../arduino/README.md).

## ▶️ Running Any Project Here

1. Open a project folder and check its `README.md` for the specific hardware and libraries.
2. Open the `.ino` file in the Arduino IDE with ESP32 board support installed.
3. Install the required libraries via the Library Manager.
4. Select the correct ESP32 board profile and serial port.
5. Wire the hardware per the pin definitions in the source code, then upload.

> **Hardware warning:** Pin assignments and power requirements should be verified before wiring. Motors, relays, and pumps typically need an external power supply and shared ground with the ESP32.

> **Wi-Fi credentials:** The [Environmental Monitoring Hub](06-environmental-monitoring-hub) ships with a placeholder Wi-Fi password (`CHANGE_ME_123`). Replace it with your own before use — never commit real credentials.

---

<p align="center"><strong>Christian G. Maranan</strong> — kréi / Krei Labs — <a href="https://github.com/krei-labs">@krei-labs</a></p>
