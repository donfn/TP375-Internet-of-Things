#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Defining an object named LCD of type LiquidCrystal_I2C
LiquidCrystal_I2C LCD(0x27, 16, 2); 

int pot = A0;


void setup()
{
// Initialises the LCD object
  LCD.init();
  // Turns on the backlight
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Hello world!");
}

void loop()
{
  LCD.setCursor(0, 1);
  LCD.print("                ");

  LCD.setCursor(0, 1);
  LCD.print(analogRead(pot), DEC);
  
  delay(350);
}
