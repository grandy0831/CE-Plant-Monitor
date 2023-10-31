#include <ESP8266WiFi.h>  // Connect to a Wi-Fi network
#include <ESP8266WebServer.h>  // Used to set up the HTTP server
#include <ezTime.h>  // For processing date and time
#include <DHT.h>
#include <DHT_U.h>  // Used to interact with the DHT22 temperature and humidity sensor

#define DHTTYPE DHT22   // The sensor type is defined as DHT22

// DHT Sensor setup
uint8_t DHTPin = 12;        // Pin 12 on the Huzzah connects to the DHT22 sensor
DHT dht(DHTPin, DHTTYPE);   // Initialize DHT sensor.              
float Temperature;          // Temperature value 
float Humidity;             // Humidity value

const char* ssid     = "xxx";
const char* password = "xxx";

ESP8266WebServer server(80);  // Create a network server instance that listens on port 80

Timezone GB;  // Create a time zone object

uint8_t soilPin = A0;   // The soil moisture sensor pin
int Moisture_val;       // Variable to store the moisture value read from the sensor

int sensorVCC = 13;    // Power pin for the sensor
int counter = 0;        // Counter to measure the soil pin resistance

void setup() {
  // open serial connection
  Serial.begin(115200);
  delay(100);

  // Start mositure sensor
  pinMode(sensorVCC, OUTPUT);
  digitalWrite(sensorVCC, LOW);  // Set the sensor power pin (sensorVCC) to output mode and set its level to low

  // start DHT sensor
  pinMode(DHTPin, INPUT);
  dht.begin(); 

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

  // when connected and IP address obtained start HTTP server  
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");

  // get real date and time
  waitForSync();
  Serial.println("UTC: " + UTC.dateTime()); 
  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());  

}

void loop() {
  counter++;
  if(counter> 6){      // change this value to set "not powered" time. higher number bigger gap
    // power the sensor
    digitalWrite(sensorVCC, HIGH);
    delay(1000);
    // read the value from the sensor:
    Moisture_val = analogRead(soilPin);   // read the resistance      
    //stop power
    digitalWrite(sensorVCC, LOW);  
    delay(100);
    counter=0;    
  }  

  server.handleClient();  // Processing requests from clients
  
  //delay(1000);
  //Serial.println(GB.dateTime("H:i:s")); // UTC.dateTime("l, d-M-y H:i:s.v T")
}

  // Get the temperature and humidity values for the DHT22 sensor 
  // and then send these values as HTML pages to the client using the ‘server.send’ method
void handle_OnConnect() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  server.send(200, "text/html", SendHTML(Temperature,Humidity,Moisture_val)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}


// Build a simple HTML page 
// Displays the temperature and humidity values detected by the DHT22 sensor
String SendHTML(float Temperaturestat,float Humiditystat, int Moisturestat){
  String ptr = "<!DOCTYPE html> <html>\n";  // Defines the basic structure of an HTML file, declares the document type and the HTML tag start
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";  // Set the viewport and zoom of the page displayed on the device
  ptr +="<title>Plant Monitor Report</title>\n";  // Set page title
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";  // Using the Style Object
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";  // Set the style of the title
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";  // Sets the style of the paragraph
  ptr +="</style>\n";
  ptr += "<script>setTimeout(function() { location.reload(); }, 1000);</script>\n"; // Refresh the page periodically
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Plant Monitor Report</h1>\n";  // The main title of the page
  
  ptr +="<p>Temperature: ";
  ptr +=Temperaturestat;
  ptr +="degC</p>";
  ptr +="<p>Humidity: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
  ptr += "<p>Soil Moisture: ";
  ptr += Moisturestat;
  ptr += "</p>";
  ptr +="<p>Sampled on: ";
  ptr +=GB.dateTime("l,");
  ptr +="<br>";
  ptr +=GB.dateTime("d-M-y H:i:s T");
  ptr +="</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
