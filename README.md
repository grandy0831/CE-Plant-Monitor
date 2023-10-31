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

### Setup Steps

#### 1. **Feather Set-up**

##### Add Feather Huzzah ESP8266 to the board manager of the [Arduino IDE](https://www.arduino.cc/en/software)

  1. Open the Arduino IDE.
  2. Go to "File" -> "Preferences".
  3. Add the following URL to the "additional development board manager URLs": 
  `https://arduino.esp8266.com/stable/package_esp8266com_index.json`
  4. After confirmation, go to "Tools" -> "Development Board" -> "Development Board Manager".
  5. In the search box, enter `ESP8266`.
  6. Install `esp8266 by ESP8266 Community`.
  7. Select `Feather Huzzah ESP8266` board.

##### Upload code to Feather Huzzah ESP8266

  1. Connect the Feather Huzzah ESP8266 to your computer via USB.
  2. Select the correct port and development board.
  3. Open a sample code, such as "Blink".
  4. Click "Upload" to upload the code to Feather Huzzah ESP8266.

Once you can get the blink example working, jump to the next step.
<br>
<br>
#### 2. **Connecting to Wifi**

  The Feather Huzzah ESP8266 is equipped with Wi-Fi capabilities. <br>
  A complete working example of the code above is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/blob/main/Connecting_to_Wifi/Connecting_to_Wifi.ino).


#### 3. **Getting the time**
#### 4. **Publish data to an MQTT server**
#### 5. **Moisture sensing**
#### 6. **Sending Soil Data to MQTT**
#### 7. **Setting up a RPi as a gateway**
#### 8. **Installing InfluxDB on RPi**
#### 9. **Installing Telegraf on RPi**
#### 10. **Installing Grafana**
#### 11. **Visualising Data on Grafana**
