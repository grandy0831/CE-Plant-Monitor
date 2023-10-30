/*
 * Getting the time
 */


#include <ESP8266WiFi.h>  //Wi-Fi related functions are provided
#include <ezTime.h>  //ezTime library

const char* ssid     = "WI-FI NAME";
const char* password = "WI-FI PASSWORD";

Timezone GB;  //Initializes a time zone object GB

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  //Connect to the specified Wi-Fi network and print a connection success message and the assigned IP address when the connection is successful

  waitForSync();  //Synchronize time from the Internet

  Serial.println("UTC: " + UTC.dateTime()); //Print the current UTC time

  GB.setLocation("Europe/London");  //Set the time zone of the GB object to the time zone of London
  Serial.println("London time: " + GB.dateTime());  //Get London time and print

}

void loop() {
  delay(1000);  //Delay 1 second
  Serial.println(GB.dateTime("l, d-M-y H:i:s.v T")); // Print the current time to the serial monitor
}

/*
 * "l"：Weekday
 * "d"：Day of the month
 * "M"：Month 
 * "y"：the last two digits of the Year 
 * "H"：hour (24 hours)
 * "i"：minutes
 * "s"：seconds
 * "v"：millisecond
 * "T"：Time Zone abbreviation
 */