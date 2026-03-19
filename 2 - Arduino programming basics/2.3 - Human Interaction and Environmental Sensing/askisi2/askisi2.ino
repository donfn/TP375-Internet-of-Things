#include <LiquidCrystal.h>

int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;

int pot = A0;

LiquidCrystal LCD(RS, EN, D4, D5, D6, D7);

void setup()
{
  LCD.begin(16, 2);
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
