// The code is based on the circuit used to test the soil moisture sensor in the Arduino environment
uint8_t soilPin = 0;   //one nail goes to +5V, the other nail goes to this analogue pin
int moisture_val;  // Used to store the humidity value read from the sensor

int sensorVCC = 13;  // Set pin D13 as the power pin for the sensor. Power is supplied to the nail by controlling the level of this pin
int counter = 0;  // Measurement of the resistance on the soil pin

void setup() {
  Serial.begin(115200);     //open serial port
  pinMode(sensorVCC, OUTPUT);
  digitalWrite(sensorVCC, LOW);  // Set the sensor power pin (sensorVCC) to output mode and set its level to low
}

void loop() {
  counter++;
  if(counter> 6){      // change this value to set "not powered" time. higher number bigger gap
    // power the sensor
    digitalWrite(sensorVCC, HIGH);
    delay(1000);
    // read the value from the sensor:
    moisture_val = analogRead(soilPin);   // read the resistance      
    //stop power
    digitalWrite(sensorVCC, LOW);  
    delay(100);
    counter=0;    
  }  
  //wait
  Serial.print("sensor = " );   // Simulated values read from the soil moisture sensor                      
  Serial.println(moisture_val);   // Displays the read value in the serial monitor
  delay(100);
}