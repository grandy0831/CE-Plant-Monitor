#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ezTime.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>

#define DHTTYPE DHT22
#define DHTPin 12
#define soilPin 0
#define sensorVCC 13
#define blueLED 2

DHT dht(DHTPin, DHTTYPE);
int lastMoisture = 0;
int Favorability = 50;
float Temperature;
float Humidity;
int Moisture = 1;

#include "password_management.h"
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

ESP8266WebServer server(80);
const char* mqtt_server = "mqtt.cetools.org";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
Timezone GB;

void setup() {
  // Initialize the Wire library and set the pin state
  Wire.begin();
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);

  pinMode(sensorVCC, OUTPUT);
  digitalWrite(sensorVCC, LOW);

  pinMode(blueLED, OUTPUT);
  digitalWrite(blueLED, HIGH);

  // Initializes serial port communication
  Serial.begin(115200);
  delay(100);

  //Initialize DHT sensor 
  pinMode(DHTPin, INPUT);
  dht.begin();

  // Start WiFi connection, web server and time synchronization
  startWifi();
  startWebserver();
  syncDate();

  // Set up MQTT server and callback function
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);
}

void loop() {
  // Handle web client requests
  server.handleClient();

  // Do the following when every minute changes
  if (minuteChanged()) {
    // Read humidity and send MQTT message
    readMoisture();
    sendMQTT();
    Serial.println(UTC.dateTime("l, d-M-y H:i:s.v T"));
  }

  // Send data to another board
  int dataM = Moisture;

  Wire.beginTransmission(13);
  Wire.write(Favorability);
  Wire.write(dataM);
  Wire.endTransmission();

  Serial.println("plant send");

  // Delay 30 seconds
  delay(30000);
  
  // Handle MQTT communication
  client.loop();

  // Calculate moisture changes and update favorability
  int moistureChange = Moisture - lastMoisture;
  lastMoisture = Moisture;

if (moistureChange > 8) {
  Favorability++;
} else if (moistureChange < 0 && Moisture < 160) {
  Favorability--; 
}

  //Limit the favorability value range to between 0 and 100
  Favorability = constrain(Favorability, 0, 100);

  // Output the favorability value
  Serial.print("Favorability: ");
  Serial.println(Favorability);
}

// Read soil moisture
void readMoisture() {
  digitalWrite(sensorVCC, HIGH);
  digitalWrite(blueLED, LOW);
  delay(100);
  Moisture = analogRead(soilPin);
  digitalWrite(sensorVCC, LOW);
  digitalWrite(blueLED, HIGH);
  delay(100);
  Serial.print("Wet ");
  Serial.println(Moisture);
}

// Start WiFi connection
void startWifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Synchronize date and time
void syncDate() {
  waitForSync();
  Serial.println("UTC: " + UTC.dateTime());
  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());
}

// Send MQTT message
void sendMQTT() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read the temperature and publish message
  Temperature = dht.readTemperature();
  snprintf(msg, 50, "%.1f", Temperature);
  Serial.print("Publish message for t: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/zczqgch/temperature", msg);

  // Read humidity and publish message
  Humidity = dht.readHumidity();
  snprintf(msg, 50, "%.0f", Humidity);
  Serial.print("Publish message for h: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/zczqgch/humidity", msg);

  // Publish soil moisture message
  snprintf(msg, 50, "%.1i", Moisture);
  Serial.print("Publish message for m: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/zczqgch/moisture", msg);

  // Publish favorability message
  int moistureChange = Moisture - lastMoisture;
  snprintf(msg, 50, "%.1d", Favorability);
  Serial.print("Publish message for Favorability: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/zczqgch/Favorability", msg);

  lastMoisture = Moisture;
}

// MQTT message callback function
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Control LED
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
}

// Reconnect to the MQTT server
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      client.subscribe("student/CASA0014/plant/zczqgch/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Start the web server
void startWebserver() {
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}

// Web request processing function
void handle_OnConnect() {
  Temperature = dht.readTemperature();
  Humidity = dht.readHumidity();
  server.send(200, "text/html", SendHTML(Temperature, Humidity, Moisture, Favorability));
}

// Page processing function not found
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

// Generate HTML content
String SendHTML(float Temperaturestat, float Humiditystat, int Moisturestat, int Favorabilitystat) {
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
  ptr += "<tr><td>Favorability</td><td>";
  ptr += Favorabilitystat;
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
