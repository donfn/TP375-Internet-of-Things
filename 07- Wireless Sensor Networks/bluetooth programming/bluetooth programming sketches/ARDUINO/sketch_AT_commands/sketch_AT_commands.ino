#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // ARDUNIO PIN 10 RX GOES TO BlueTooth TX AND
                                //ARDUINO PIN 11 TX GOES TO BlueTooth RX
 
void setup()
{
  Serial.begin(9600);
  BTserial.begin(38400);  //Baud Rate for command Mode. 
  Serial.println("Enter AT commands!");
}
 
void loop()
{
 
  // Feed any data from bluetooth to Terminal.
  if (BTserial.available())
    Serial.write(BTserial.read());
 
  // Feed all data from termial to bluetooth
  if (Serial.available()){
    int data=Serial.read();
    Serial.write(data);    //echo
    BTserial.write(data);
    data="";

  }
}
