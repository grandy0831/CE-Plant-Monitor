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
  A complete working example of the code is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/blob/main/Connecting_to_Wifi).
<br>
<br>

#### 3. **Getting the time**

  In this step, you will learn to get time from the Internet, which is very important for subsequent data acquisition and recording.<br>
  A complete working example of the code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/blob/main/Getting_the_time).<br><br> 
  <img width="890" alt="Getting_the_time_monitor_output" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/9de2e704-bc97-4302-9831-8ab660412a97">
<br>
<br> 

#### 4. **Publish data to an MQTT server**

  We will be sending data to a MQTT server.<br> 
 A complete working example of the code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/Publish_data_to_an_MQTT_server).<br> <br> 
 <img width="1020" alt="MQTT" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/29e8fe25-3ba4-4862-8ff9-8c36f5f30eb0">
<br>
<br> 
 
#### 5. **Moisture sensing**

  The sensor of the plant monitor is based on two parts - a DHT22 temperature/humidity sensor and a pair of nails. While the former exists in convenient, accurate, and packaged form, the latter requires a lot more creativity and tinkering to make it work. We'll start by creating a soil sensor.
<br> <br> 
  The basic principle is to measure the soil resistance between two nails that are separated by a distance. The higher the water content in the soil, the lower the electrical resistance. There are many challenges with nails, from electrolysis to determining the meaning of the simulated reading (It depends on nail length, soil depth, soil type, distance between nails, etc.).
<br> <br> 
The Fritzing diagram below shows the circuit for connecting a soil sensor using 2 nails and a DHT22 sensor.<img width="1076" alt="e38e251e2e837937" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/28a1031e-ee9c-40a5-95b1-d36f85851975"><img width="1201" alt="14e0883730a7e435" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/d1f01d2b-432b-4da2-b99b-bcc1dbd9dc49">![dfb2411573027bfe](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/59cebb80-8e7a-4c2b-a6ed-c26a9797834f)<br>
To test the soil sensor build the circuit <br><br>
A complete working example of the code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/Moisture_sensing).
<br>
<br>
  
#### 6. **Generate an HTML page**
A complete working example of the code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/Generate_an_HTML_page).<br>
![截屏2023-10-31 02 49 22](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/3ec945c3-5ed2-47fb-ab6b-13050adc3c08)<br><br>
You can also change the style to create the table yourself.![截屏2023-10-31 03 18 43](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/d84293a6-5bc0-4d3b-9eb4-416884665958).
<br>
<br>


#### 7. **Sending Soil Data to MQTT**
#### 8. **Setting up a RPi as a gateway**
#### 9. **Installing InfluxDB on RPi**
#### 10. **Installing Telegraf on RPi**
#### 11. **Installing Grafana**
#### 12. **Visualising Data on Grafana**
