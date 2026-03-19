#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // ARDUNIO PIN 10 RX GOES TO BlueTooth TX AND
                                //ARDUINO PIN 11 TX GOES TO BlueTooth RX

char          input;
double        reading;
unsigned long previous = 0;

int led = 13;
int pot = A0;

void setup()
{
  pinMode(led, OUTPUT);
  BTserial.begin(38400);
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  if (BTserial.available())
  {
    input = BTserial.read();
    if (input == '1')
    {
      digitalWrite(led, HIGH);
    }
    if (input == '0')
    {
      digitalWrite(led, LOW);
    }
  }    
  if (millis() > previous + 1000)
  {
    previous = millis();

    BTserial.println( analogRead(pot) );
    Serial.println(analogRead(pot));      //for debugging
    Serial.println(input);                //for debugging
  }  
}
