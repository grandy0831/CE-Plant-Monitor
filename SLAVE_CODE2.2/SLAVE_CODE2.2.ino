#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(0, 1, 8, 9, 10, 11); /// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN

int Favorability;
int dataM;

void setup() 
{
  Wire.begin(13);// Initialize I2C communication and set Arduino's I2C address to 13
  lcd.begin(16, 2);//Initialize LCD, set to 16 columns and 2 rows
}

void receiveEvent(int bytes) 
{
  Favorability = Wire.read(); // Read the Favorability data received via I2C
  dataM = Wire.read();       // Read the Moisture data received via I2C
}

void loop() 
{

  Wire.onReceive(receiveEvent); // Call the receiveEvent function when I2C receives data

  lcd.setCursor(0, 0); // Set LCD cursor to column 0, row 0
  lcd.print("FAVORABILITY:"); // Display "FAVORABILITY:" on LCD
  lcd.setCursor(14, 0); 
  lcd.print(Favorability); 
  lcd.setCursor(0, 1); 
  lcd.print("MOI:");
  lcd.setCursor(4, 1);
  lcd.print(dataM);

  lcd.setCursor(7, 1); 
    if (Favorability < 20) {
      lcd.print(" SAD :(");
    } else if (Favorability >= 20 && Favorability <= 50) {
      lcd.print(" HAPPY :)");
    } else {
      lcd.print(" EXCITED :)");
    }
  }
