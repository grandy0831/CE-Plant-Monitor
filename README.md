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

  6.Modify the arrow section of the following images.<br><br>
[Images here](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/img)

<br><br>

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
<img width="1833" alt="da7a8ad62ca5a6ab" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/f8671fc3-cf03-4c22-8698-68de569c502f"><img width="1304" alt="截屏2023-11-01 10 17 23" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/e8bc7ee1-bf7b-4de9-8d22-3c0fb341b76d">
<br><br>


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
<img width="1646" alt="截屏2023-11-10 19 14 21" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/6daa900f-5178-458f-ae2d-1cc51ba85fe2">
<br><br>
Your data is displayed on Grafana(The above shows the storage data for two days).
<br><br>
<hr>

>Now let's branch out and do some fun ideas, like create a plant pet based on our plant monitor.
# Plantpets 🌱🐾
Welcome to the Plant Pet Project! This is a combination of plant monitor features to create a prototype of a fun plant pet. The project allows you to interact with your plants, monitor their status and provide care.
>‼️Important note: this is an unfinished concept project, I will try my best to complete this project, only part of the code can run at present, I am trying to implement the project.<br>

## Functions and features(Prediction)
- **Emotional feedback** : LED lights or displays show the emotional state of the plant.<br><br>
***1.LED light emotional feedback***<br><br>
  LED light color change: Use different colors of LED lights to convey different emotional states. For example, green represents health, red represents the need for water, yellow represents happiness and so on. Write code to control the color change of the LED according to the preset state.<br><br>
***2.Display affective feedback***<br><br>
  Use a small display(`LCD` or `OLED`) that displays plant expressions or ICONS to convey different emotional states.Corresponding text descriptions or animations are displayed on the display to convey the emotional state of the plant. For example, `"I'm thirsty"` means water is needed, or an animation shows the state of the plant.<br><br>
Other preparatory work：<br><br>
- On the Feather Huzzah ESP8266:<br><br>
  Prepare sensors and acquire data: First, connect plant monitoring sensors to the Feather Huzzah ESP8266. And then get plant status information from sensors, such as humidity, temperature, etc.<br><br>
  Sending data using I2C: Configure the Feather Huzzah ESP8266 as the I2C master device using the Arduino IDE and Wire library to send plant status information.<br><br>

- On the Arduino UNO:<br><br>
  Prepare the LCD display: Connect the LCD display to the Arduino UNO and make sure you are able to control the LCD using the LiquidCrystal library through the Arduino IDE.<br><br>
  I2C communication Settings: Configure the Arduino UNO as the I2C slave device. Receive data sent from Feather Huzzah ESP8266.<br><br>
  Receive and display data: Write code to receive data from the Feather Huzzah ESP8266 on UNO and then display the corresponding plant status information on the LCD.<br><br>

Here is a simple way to connect an LCD using an Arduino UNO:<br><br>
![20210520141046318](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/fd9e05a2-89f4-4ad0-a44a-ba420d245b29)<br><br>
The diagram above shows the circuit diagram of a 16x2 LCD connected to the ARDUINO UNO.<br><br>
A complete working example of the code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/LCD).<br><br>
<img width="1321" alt="截屏2023-11-01 01 57 14" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/2572e4a8-2c50-47dd-9edd-e85469256f14"><br><br>
<img width="1320" alt="截屏2023-11-01 01 57 27" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/e9b544a2-3eb6-4d20-87cf-99dad26e6e55">

<br><br>
- <strong>Arduino——I2C communication:</strong><br><br>
<strong>Arduino I2C communication pins:</strong><br><br>
For I2C communication, different boards for Arduino have different pins dedicated to the SDA and SCL pins<br><br>
1. In Arduino UNO, pin A4 = SDA, pin A5 = SCL.<br><br>
2. In Feather Huzzah ESP8266, pin SDA/4 = SDA, pin SCL/5 = SCL.<br><br>
![image](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/bfeafe64-41ed-4f3a-89f7-e95db77d05f2)<br><br>
[This website](https://blog.csdn.net/m0_46152804/article/details/125130186?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169877625716800184144928%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169877625716800184144928&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_click~default-1-125130186-null-null.142^v96^pc_search_result_base7&utm_term=Arduino%20I2C%20&spm=1018.2226.3001.4187) provides a complete explanation of the working principle of I2C communication.<br><br>

Arduino I2C host code<br><br>

    #include <Wire.h>
    int LED=13;
    int x = 0;
    
    void setup() 
    {
      Wire.begin(); 
      Serial.begin(9600);
      pinMode(LED,OUTPUT);
    }
    
    void loop() 
    {
      Wire.beginTransmission(9);
      Wire.write(x);              
      Wire.endTransmission();
     
      x++;
      if (x > 6) 
      {
        x = 0;
      }
      delay(200);
    }


Arduino I2C slave code<br><br>

    #include <Wire.h>
    int LED = 13;
    int x = 0;
    
    void setup() 
    {
      pinMode (LED, OUTPUT);
      Wire.begin(9); 
      Wire.onReceive(receiveEvent);
      Serial.begin(9600);
    }
    
    void receiveEvent(int bytes) 
    {
      x = Wire.read();
    }
    
    void loop() 
    {
      if (x <= 3) 
      {
        digitalWrite(LED, HIGH);
      }
      else 
      {
        digitalWrite(LED, LOW);
      }
    }

Adding Arduino i2C communication to our code <br><br>
Arduino I2C host code<br><br>
A complete working example of the code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/Plant_Monitor_HOST_CODE).<br><br>

Arduino I2C slave code<br><br>
A complete working example of the code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/SLAVE_CODE).<br><br>

In this way, we can send the plant data to the LCD display screen!<br><br>
![image](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/76b50a37-1424-4497-9780-82b60393085e)<br><br>
When the humidity is less than 180, let the LCD display "I'm thirsty :(" to remind us to water the plantpet.<br><br>
![image](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/f34fcff7-8e6c-4443-8ee5-0b823518ce31)<br><br>
When the humidity is greater than 180, let the LCD display "HAPPY :)" and let the plantpet tell us that it is happy.<br>
![image](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/7a4aa91e-8cf9-432f-b896-eacd706d21eb)<br><br>
![image](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/90932057-09eb-49fd-b8fc-40120aae155f)<br>

>In the "Plantpets" project, we introduced an innovative element—Favorability. The concept was conceived to establish a deeper and more interactive relationship between plants and users. Inspired by the classic interaction mechanism of electronic pets, we aim to focus more on caring for our plants through the introduction of favorability.

## Definition of Favorability

Favorability is a quantifiable metric that reflects the plant's perception of your care. Through sensors, we capture the plant's status (moisture) and translate it into a numerical value for favorability. Changes in favorability are directly related to the plant's emotional state. Increasing favorability indicates the plant's happiness, while a decrease may signal the plant's discomfort.

## Interaction Mechanism

With favorability introduced, the interaction between us and the plant is no longer one-sided. By interacting with the plant, especially by promptly meeting the plant's needs (such as watering), you can increase the plant's favorability. This process is not just about caring for the plant but also serves as a medium to establish emotional connections between you and the plant.

## Favorability Display

To provide an intuitive understanding of the plant's emotional state, we display favorability in real-time on an LCD screen. From "happy :)" to "sad :(" and even to "excited ：）," we can better understand the plant's current feelings based on the displayed expressions and status information.<br>

![WechatIMG239](https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/1524d916-4f52-4d08-addf-6a7968094427)

Host code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/Plant_Monitor_HOST_CODE2.2).<br><br>
Host code  is [available here on GitHub](https://github.com/grandy0831/CE-Plant-Monitor/tree/main/SLAVE_CODE2.2).<br>

**Note:** Ensure to interact with the plant according to the favorability information displayed on the LCD screen to maintain the plant's well-being and emotional state.
---


- Power supply method:<br><br>
I tried to use a 10,000 mAh power bank to power Feather Huzzah ESP8266 and Arduino UNO at the same time. I connected the power supply at 10:30 am on November 1st. According to the data in the database, after 1:30pm on November 3rd No data is received, indicating that the power bank is exhausted. During this period, the power bank continued to provide power for a total of 51 hours.<br><br>
<img width="1728" alt="截屏2023-11-08 14 30 42" src="https://github.com/grandy0831/CE-Plant-Monitor/assets/140076679/de9d889a-1be2-4543-8e38-856b5749500c"><br><br>







>The above are the functions of plant pets that have been implemented. None of the functions mentioned below have been implemented. Currently, they are only showing related concepts, but please don’t worry, I will keep updating this readme to improve the plantpet.

- **Sound feedback** : Plant pets make sounds to express needs or emotions.<br><br>
Increase the interactivity and fun of plant pets while helping users better understand the state and needs of plants<br><br>
>Use a buzzer or speaker<br><br>

- **Interactive** : Users can give water or care to plant pets with a button or touch sensor.<br><br>
By adding interactivity, users will be able to interact more directly with plant pets, which will improve the user experience and make users more willing to care about the health of the plant<br><br>
>knob control, touch sensor or distance sensor.<br><br>

- **Automatic watering system** : Water plants automatically according to soil moisture sensor data.<br><br>
>Exploring<br><br>

- **Data visualization** : Displays plant health, humidity, light and other data.<br><br>
>Grafana, Web, Mobile APP, LED, Displays.<br><br>

- **Remote Control** : Users can monitor and interact with plant pets remotely, no matter where they are.<br><br>
