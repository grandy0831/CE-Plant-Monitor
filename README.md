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

A complete working example of the code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/Generate_an_HTML_page).<br><br>
![截屏2023-10-31 02 49 22](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/3ec945c3-5ed2-47fb-ab6b-13050adc3c08)<br><br>
You can also change the style to create the table yourself.<br><br>![截屏2023-10-31 03 18 43](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/d84293a6-5bc0-4d3b-9eb4-416884665958)
<br>
<br>


#### 7. **Sending Soil Data to MQTT**

A complete working example of the code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/Plant_Monitor).<br><br>
The data should now flow from the Huzzah plant monitor to the MQTT web server and be locally visible by browsing the device's IP address.<br><br>
<img width="1016" alt="截屏2023-10-31 23 52 12" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/51617567-fdc2-4a6f-b6b0-0372df959cd1"><br><br>
![截屏2023-10-31 03 11 24](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/6f44aa5b-a94d-4f6b-b73c-918c02cf3481)<br><br>


#### 8. **Setting up a RPi as a gateway**

In this step, we configured the Raspberry PI as a data gateway to collect and process data from the plant monitor.<br><br>
[This page](https://www.raspberrypi.com/software/) can help you set up your Raspberry PI.<br><br>

<img width="792" alt="7195b6768554ba3c" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/9222f89c-151b-49be-bb6f-61326d923331"><br><br>
On your Mac / PC open up a Terminal / Putty session and log into the device using SSH.

    ssh USERNAME@YOURHOSTNAME.local

To check the OS of the device enter the following:

    cat /etc/os-release
Finally do a quick update / upgrade to make sure all files are upto date and then reboot before moving on to installing the datastore.

    sudo apt update
    sudo apt upgrade -y
    sudo reboot
<br><br>

#### 9. **Installing InfluxDB on RPi**
InfluxDB downloads are [available here](https://portal.influxdata.com/downloads/#influxdb).We will use the Ubuntu & Debian (Arm 64-bit) option.
<br><br>
  1.Add the InfluxDB key to ensure secure download and the repository to the sources list so that we can download it in the next step.
  
    wget -q https://repos.influxdata.com/influxdata-archive_compat.key
    echo '393e8779c89ac8d958f81f942f9ad7fb82a25e133faddaf92e15b16e6ac9ce4c influxdata-archive_compat.key' | sha256sum -c && cat influxdata-archive_compat.key | gpg --dearmor | sudo tee /etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg > /dev/null
    echo 'deb [signed-by=/etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg] https://repos.influxdata.com/debian stable main' | sudo tee /etc/apt/sources.list.d/influxdata.list
  2.With the repository added we now run another update to the package list
  
    sudo apt-get update
    
  3.Finally we install InfluxDB

    sudo apt-get install influxdb2 -y

  4.Finally to get InfluxDB up and running at reboot we need to enable and start it within systemctl

    sudo systemctl unmask influxdb.service
    sudo systemctl start influxdb
    sudo systemctl enable influxdb.service
    sudo systemctl status influxdb

  Use `CTRL C` to break out of the systemctl command and get back to the terminal prompt.<br><br>
  ![截屏2023-11-01 00 14 51](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/27f9b257-ec90-4e07-9f2d-b7aa206c6987)
<br><br>

  
#### 10. **Installing Telegraf on RPi**
  Telegraf is a time-series data collector.<br><br>
  1.Get back to the terminal on the RPi and install telegraf using the following command:

    sudo apt-get update && sudo apt-get install telegraf -y
    
  2.define some PATH variables:
  
    export INFLUX_HOST=http://10.129.101.214:8086
    export INFLUX_ORG=casa0014 
    
>you will need to change your host IP address to the one assigned to your RPi - you can find out your IP address by typing `ifconfig` at the command line.<br><br>
  3.The third PATH variable you need to set is the `TOKEN` to get access to the `Bucket`.

    export INFLUX_TOKEN=---you-will-have-your-own-token-here---

  4.Finally you need to run telegraf and pass in the configuration file it needs to use - again we need to edit the command to replace the hostname with the IP address. 

    telegraf --config http://10.129.101.214:8086/api/v2/telegrafs/0a2093eea36cb000

>You can `COPT TO CLIPBOARD `from `3.Start Telegraf`.<br><br>

  ![截屏2023-11-01 00 14 51](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/56ed9711-096f-4351-a5c6-0bb685bd4c13)<br><br>

  5.Open up the [file on sample v2 configuration file on GitHub](https://github.com/ucl-casa-ce/casa0014/blob/main/plantMonitor/pi%20config/etc/telegraf/telegrafv2.conf) since we will use this as the basis for setting up your configuration file.<br><br>

  6.Modify the arrow section of the following image.<br><br>
<img width="793" alt="7f13be0f583dcdad" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/23516b1b-628d-441a-a33f-c51c3564de51">
<img width="800" alt="b4f2ccf0de206801" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/2d7931ac-ad9c-4db1-a8ef-1c5753aa939c"><br><br>

  7.Save the file and then we will copy it across to the RPi.
  
    sudo mv /etc/telegraf/telegraf.conf /etc/telegraf/telegraf-original.conf
    sudo nano /etc/telegraf/telegraf.conf

  8.Restart the influxdb service for the configurations to be set and check the status:

    sudo systemctl stop influxdb
    sudo systemctl start influxdb
    sudo systemctl status influxdb
    sudo systemctl start telegraf
    sudo systemctl status telegraf

  >If you have any problems running, remember `sudo systemctl stop influxdb` and `sudo systemctl stop telegraf` before start them.<br><br>

  9.You should now be able to explore the data through the Data Explorer<br><br>
<img width="1833" alt="da7a8ad62ca5a6ab" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/f8671fc3-cf03-4c22-8698-68de569c502f"><br><br>


#### 11. **Installing Grafana**
In the final step we will install Grafana so that we can visualise the data in the InfluxDB. <br><br>
 1.Install:

    sudo apt-get install -y adduser libfontconfig1 musl
    wget https://dl.grafana.com/enterprise/release/grafana-enterprise_10.1.5_arm64.deb
    sudo dpkg -i grafana-enterprise_10.1.5_arm64.deb

 2.add grafana to systemd and then to start the service:

    sudo /bin/systemctl daemon-reload
    sudo /bin/systemctl enable grafana-server
    sudo /bin/systemctl start grafana-server

#### 12. **Visualising Data on Grafana**

Open your browser and go to the address `http://staff-pi-casa0014.local:3000`, where the middle bit is the Raspberry Pi address.

In the middle of the dashboard you should see a prompt to `Add your first datasource` click on that and fill out the following details:

- select InfluxDB
- select Flux as the Query Language (needed for v2 of InfluxDB)
- add `http://127.0.0.1:8086` at the URL
- deselect `basic auth`
- add org name and copy in your user API token from InfluxDB
- add `mqtt-data` as the default bucket
<br><br>
<img width="1300" alt="截屏2023-10-31 17 03 10" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/2799de3d-6708-4f3d-83a8-0f1254bcc459"><br><br>
Your data is displayed on Grafana.
---
>Now let's branch out and do some fun ideas, like create a plant pet based on our plant monitor.
# Plantpets 🌱🐾
