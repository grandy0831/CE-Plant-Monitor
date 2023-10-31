#include <ESP8266WiFi.h>           // Library to enable ESP8266 WiFi functionality
#include <ESP8266WebServer.h>      // Library to set up the HTTP server
#include <ezTime.h>                // Library to set up the HTTP server
#include <PubSubClient.h>          // Library for MQTT communication
#include <DHT.h>                   // Library to interact with the DHT22 temperature and humidity sensor
#include <DHT_U.h>                 // Additional library for DHT sensors

#define DHTTYPE DHT22              // Define the sensor type as DHT22

// Define the pin for the DHT22 sensor
uint8_t DHTPin = 12;
// Define the pin for the soil moisture sensor
uint8_t soilPin = 0;
// Variable to store temperature value
float Temperature;
// Variable to store humidity value
float Humidity;
// Variable to store moisture value
int Moisture = 1;
// Pin used to control the power to the sensor
int sensorVCC = 13;
// Pin for the blue LED status indicator
int blueLED = 2;
// Initialize the DHT sensor object
DHT dht(DHTPin, DHTTYPE);   


// Network and MQTT configuration
#include "password_management.h" 

// Please enter your sensitive data in the Secret tab/password_management.h
const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

ESP8266WebServer server(80);
const char* mqtt_server = "mqtt.cetools.org";      // MQTT server address
WiFiClient espClient;                              // Create a WiFi client
PubSubClient client(espClient);                    // Initialize the MQTT client
long lastMsg = 0;                                  // Variable to store the timestamp of the last message
char msg[50];                                      // Buffer to hold the message data
int value = 0;                                     // Variable for message value

// Timezone setup
Timezone GB;


// sets up the various pins for input and output
// initializes the serial communication for debugging
// starts the DHT sensor
// initializes the WiFi connection, web server, and MQTT server
// synchronizes the date and time
void setup() {
  // Set up LED to be controllable via broker
  // Initialize the BUILTIN_LED pin as an output
  // Turn the LED off by making the voltage HIGH
  pinMode(BUILTIN_LED, OUTPUT);     
  digitalWrite(BUILTIN_LED, HIGH);  

  // Set up the outputs to control the soil sensor
  // switch and the blue LED for status indicator
  pinMode(sensorVCC, OUTPUT); 
  digitalWrite(sensorVCC, LOW);

  pinMode(blueLED, OUTPUT); 
  digitalWrite(blueLED, HIGH);

  // Initialize serial communication for debugging
  Serial.begin(115200);
  delay(100);

  // start DHT sensor
  // Initialize the DHT sensor
  pinMode(DHTPin, INPUT);
  dht.begin();

  // run initialisation functions
  // start the web server
  // synchronize the date and time
  startWifi();
  startWebserver();
  syncDate();

  // start MQTT server
  // Set the callback function for MQTT
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);

}

void loop() {
  // Handle web server clients
  server.handleClient();
  // Print the time
  if (minuteChanged()) {
    readMoisture();
    sendMQTT();
    Serial.println(UTC.dateTime("l, d-M-y H:i:s.v T")); // GB.dateTime("H:i:s")
  }
  
  client.loop();
}

// Function to read moisture from the soil sensor
void readMoisture(){
  
  // power the sensor
  digitalWrite(sensorVCC, HIGH);
  // Turn on blue LED as an indicator
  digitalWrite(blueLED, LOW);
  delay(100);
  // Read the moisture value
  Moisture = analogRead(soilPin);
  // Turn off the sensor       
  digitalWrite(sensorVCC, LOW);
  // Turn off the blue LED
  digitalWrite(blueLED, HIGH);
  delay(100);
  Serial.print("Wet ");
  // read the value from the nails
  Serial.println(Moisture);
}

// Function to establish WiFi connection
void startWifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // check to see if connected and wait until you are
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to synchronize date and time
void syncDate() {
  // get real date and time
  waitForSync();
  Serial.println("UTC: " + UTC.dateTime());
  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());

}

// Function to send data via MQTT
void sendMQTT() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  Temperature = dht.readTemperature();  // Read temperature from DHT sensor
  snprintf (msg, 50, "%.1f", Temperature);  // Format the message
  Serial.print("Publish message for t: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/zczqgch/temperature", msg);  // Publish temperature data

  Humidity = dht.readHumidity();  // Read humidity from DHT sensor
  snprintf (msg, 50, "%.0f", Humidity);  // Format the message
  Serial.print("Publish message for h: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/zczqgch/humidity", msg);  // Publish humidity data

  //Moisture = analogRead(soilPin);   // Read moisture from readMoisture function
  snprintf (msg, 50, "%.0i", Moisture);  // Format the message
  Serial.print("Publish message for m: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/zczqgch/moisture", msg);  // Publish humidity data

}

// MQTT callback function
void callback(char* topic, byte* payload, unsigned int length) {
  // Handle received MQTT messages
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

// Attempt to reconnect to the MQTT broker
void reconnect() {
  // Loop until reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect with clientID, username and password
    if (client.connect(clientId.c_str(), SECRET_MQTTUSER, SECRET_MQTTPASS)) {
      Serial.println("connected");
      // Resubscribe to topics after successful connection
      client.subscribe("student/CASA0014/plant/zczqgch/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// Start the web server
void startWebserver() {
  // when connected and IP address obtained start HTTP server  
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");  
}

// Handling the root path connection
void handle_OnConnect() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity
  server.send(200, "text/html", SendHTML(Temperature, Humidity, Moisture));
}

// Handling 'Not Found' responses
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

// Generate the HTML content with the temperature, humidity, and moisture values
String SendHTML(float Temperaturestat, float Humiditystat, int Moisturestat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Plant Monitor Report</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "table {border-collapse: collapse; width: 50%; margin: 0 auto;}\n";
  ptr += "th, td {border: 1px solid #dddddd; text-align: left; padding: 8px;}\n";
  ptr += "th {background-color: #f2f2f2;}\n";
  ptr += "td {background-color: #ffffff;}\n";
  ptr += "</style>\n";
  ptr += "<script>setTimeout(function() { location.reload(); }, 1000);</script>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Plant Monitor Report</h1>\n";

  ptr += "<table>\n";
  ptr += "<tr><th>Measurement</th><th>Value</th></tr>";
  ptr += "<tr><td>Temperature</td><td>";
  ptr += (int)Temperaturestat;
  ptr += "&deg;C</td></tr>";
  ptr += "<tr><td>Humidity</td><td>";
  ptr += (int)Humiditystat;
  ptr += "%</td></tr>";
  ptr += "<tr><td>Moisture</td><td>";
  ptr += String(Moisturestat);
  ptr += "</td></tr>";
  ptr += "<tr><td>Sampled on</td><td>";
  ptr += GB.dateTime("l, d-M-y H:i:s T");
  ptr += "</td></tr>";
  ptr += "</table>\n";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
