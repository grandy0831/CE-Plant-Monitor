#include <ESP8266WiFi.h> // The ESP8266 Wi-Fi library is introduced，I can use the functions and methods in it to connect to a Wi-Fi network

const char* ssid     = "WIFINAME";  // Replace with the name of my Wi-Fi network
const char* password = "WIFIPASSWORD";  // Replace it with my Wi-Fi password
const char* host = "iot.io";  // Declare the Web host to connect to，specifies the address of the Web host to connect to

void setup() {
  Serial.begin(115200);  // To initialize serial port communication, use baud rate 115200
  delay(100);  // A short delay to ensure serial port initialization is complete

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

void loop() {
  delay(5000);  // 5 second delay

  Serial.println("-------------------------------");  // Indicates that a connection attempt is in progress
  Serial.print("Connecting to ");  // Indicates that a connection attempt is in progress
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  // Builds and executes an HTTP GET request to get Web page data from a specified URI (Uniform Resource Identifier)
  
  String url = "/index.html";
  Serial.print("Requesting URL: ");
  Serial.println(host + url);  // The URL being requested is displayed

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  delay(500);   // The ESP8266 will send an HTTP GET request to the specified URL and wait for the server to respond. The server returns the requested Web page data
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection"); // Once all the response data has been read and printed, the connection to the server will be closed
}
