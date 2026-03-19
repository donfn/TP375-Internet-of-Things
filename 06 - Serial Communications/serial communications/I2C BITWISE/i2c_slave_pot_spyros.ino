//SLAVE SENDING POT VALUE
#include <Wire.h>
//#include <I2C_Anything.h>

void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);
  Wire.begin(8); 
  Wire.onRequest(requestEvent); 
}
void loop() {
  delay(100);
}
void requestEvent() {
  int pot = analogRead(A0);
  Wire.write (pot >> 8);   
  Wire.write (pot & 0xFF); 
  Serial.println(pot);
   //int pot = analogRead(A0);
  //I2C_writeAnything(pot);
}

