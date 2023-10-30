#include <ESP8266WiFi.h>
#include <PubSubClient.h>  // Introducing libraries related to ESP8266 Wi-Fi and MQTT

// Wifi and MQTT
#include "password_management.h"   // Used to store password data
/*
**** please enter your sensitive data in the Secret tab/password_management.h
**** using format below

#define SECRET_SSID "ssid name"
#define SECRET_PASS "ssid password"
#define SECRET_MQTTUSER "user name - eg student"
#define SECRET_MQTTPASS "password";
 */

const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;


const char* mqtt_server = "mqtt.cetools.org";  // Enter the URL of the MQTT server, indicating the address of the MQTT server to connect to

WiFiClient espClient;
PubSubClient client(espClient);  // Used for Wi-Fi communication and MQTT communication
long lastMsg = 0;  // Used to track the last message sent
char msg[50];  // Used to store message content, limited to 50 characters
int value = 0;


void setup() {


  // Initialize the built-in LED and MQTT clients
  pinMode(BUILTIN_LED, OUTPUT);  // Set the built-in LED to output mode
  digitalWrite(BUILTIN_LED, HIGH);  // Set the built-in LED to high (usually indicates LED off)

  // open serial connection via the wifi to the mqtt broker
  Serial.begin(115200);
  delay(100); // to give time for the serial connection to open

  // Initiate the connecting to wifi routine
  startWifi();

  // Once connected to wifi establish connection to mqtt broker
  client.setServer(mqtt_server, 1884);

  // The callback in this case listens for instructions to 
  // change the state of the LED - here we are initialising 
  // that function
  client.setCallback(callback); 


}


// Send messages to the MQTT server
void loop() {
  delay(5000);
  sendMQTT();
}

void startWifi(){
  // We start by connecting to a WiFi network
  // Initialize the serial communication, then try to connect to the specified Wi-Fi network, while providing some debugging information in the serial monitor so that the status of the connection can be tracked
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);  // Used to print debugging information on the serial port monitor
  WiFi.begin(ssid, password);  // Connect to a Wi-Fi network

  while (WiFi.status() != WL_CONNECTED) {  // Wait for connection
  delay(500);
  Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  // To indicate successful connection
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  // Print the local IP address
}

// Publishes formatted messages to the specified MQTT topic
// The message content to be published is printed using the serial port monitor
void sendMQTT() {

  // Check whether the MQTT client is connected. If not, call the reconnect() function to reconnect
  if (!client.connected()) {
    reconnect();
  }  
  // Execute the loop() function on the MQTT client to process messages from the MQTT server
  client.loop();
  ++value;  // Track the number of messages sent to the server
  // Format the message for sending to the MQTT server
  snprintf (msg, 50, "hello world #%ld", value);
  // Output a message sending prompt on the serial port monitor
  Serial.print("Publish message: ");
  // Output the message to be sent on the serial port monitor
  Serial.println(msg);
  // Using MQTT client the publish () function will be released news MSG to the theme of "student/CASA0014 / plant/zczqgch"
  client.publish("student/CASA0014/plant/zczqgch", msg);
}


// It is used to reconnect to the MQTT server
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {    // while not (!) connected....
    Serial.print("Attempting MQTT connection...");  // Output a connection attempt message on the serial monitor
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    // If connection is successful
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");  // If connected is displayed on the serial port monitor, the connection is successful
      // ... and subscribe to messages on broker
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

// Process messages received by subscribed MQTT topics
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");  // Displays a reminder of received messages on the serial port monitor, including the subject of the message
  Serial.print(topic);  // Displays the subject of the received message
  Serial.print("] ");  // Loop through and print the content of the received message.
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
