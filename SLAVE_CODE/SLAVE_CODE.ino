#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(0, 1, 8, 9, 10, 11); /// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN

int dataT ;
int dataH ;
int dataM ;

void setup() 
{
  Wire.begin(13);// Initialize I2C communication and set Arduino's I2C address to 13
  lcd.begin(16, 2);//Initialize LCD, set to 16 columns and 2 rows
}

void receiveEvent(int bytes) 
{
  dataT = Wire.read();//Read the temperature data received via I2C
  dataH = Wire.read();//Read the Humidity data received via I2C
  dataM = Wire.read();//Read the Moisture data received via I2C

}

void loop() 
{

  Wire.onReceive(receiveEvent);//Call the receiveEvent function when I2C receives data

  lcd.setCursor(0, 0);//Set the LCD cursor to column 0, row 0
  lcd.print("TEM:");// Display "TEM:" on LCD
  lcd.setCursor(4, 0);//Set the LCD cursor to column 4, line 0
  lcd.print(dataT);//Display temperature value on LCD
  lcd.setCursor(8, 0);//Set the LCD cursor to column 8, row 0
  lcd.print("HUM:");// Display "HUM:" on LCD
  lcd.setCursor(12, 0);//Set the LCD cursor to column 12, line 0
  lcd.print(dataH);//Display humidity value on LCD
  lcd.setCursor(0, 1);//Set the LCD cursor to column 0, row 1
  
  if (dataM < 180) {
    lcd.print("I'M THIRSTY :("); // When the humidity value is less than 180, display "I'M THIRSTY :(" on the LCD
  } else {
    lcd.print("MOI:");// Display "MOI:" on LCD
    lcd.setCursor(4, 1);//Set the LCD cursor to column 4, row 1
    lcd.print(dataM);//Display humidity value on LCD
    lcd.setCursor(7, 1);//Set the LCD cursor to column 7, row 1
    lcd.print(" HAPPY :)");// Display "HAPPY :)" on LCD
  }
}