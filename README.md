# 🌳 Plant-Monitor

## Overview
>The project is a plant monitor designed to monitor the plant's environment such as soil moisture of plants, while using Feather Huzzah ESP8266 Wi-Fi connection and MQTT server to publish sensor data, and using RPi gateway to store and visualize time series data.

## Function
- Real-time monitoring of plant temperature and humidity and moisture.
- Collect data through sensors and send it to a cloud database.
- Data can be transmitted through MQTT protocol.
- Stores data on the RPi gateway.
- Visualize time series data.

## Installation
### Materials required
- [Arduino IDE](https://www.arduino.cc/en/software)
- [Feather Huzzah ESP8266](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/overview)
- DHT22
- [Raspberry Pi](https://www.raspberrypi.com/software/)
- [MQTT Explorer](https://mqtt-explorer.com/)

### Setup steps
1. **Feather Set-up**
2. **Connecting to Wifi**
3. **Getting the time**
4. **Publish data to an MQTT server**
5. **Moisture sensing**
6. **Sending Soil Data to MQTT**
7. **Setting up a RPi as a gateway**
8. **Installing InfluxDB on RPi**
9. **Installing Telegraf on RPi**
10. **Installing Grafana**
11. **Visualising Data on Grafana**
