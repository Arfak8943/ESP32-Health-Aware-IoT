# ESP32-Health-Aware-IoT
An IoT-based self-diagnosing system using ESP32, DHT22, and Blynk Cloud.


This project monitors the "health" of a system using an ESP32. It calculates a health score based on temperature and current draw, logs failures to Flash memory, and sends live data to a Blynk IoT dashboard.

## Features
* **Real-time Monitoring:** DHT22 for heat and Potentiometer for current.
* **Diagnostic Logic:** Calculates a 0-100% health score.
* **Cloud Integration:** Live dashboard via Blynk.
* **Fail-Safe:** Automatic LED alarm during critical failures.

## Hardware Used (Simulated)
* ESP32
* DHT22 Temperature Sensor
* 16x2 I2C LCD
* Sliding Potentiometer
