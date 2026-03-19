//MASTER REQUESTING  POT VAL
#include <Wire.h>
//#include <I2C_Anything.h>

void setup() {
  pinMode(11,OUTPUT);
  Wire.begin();
  Serial.begin(9600); 
}
void loop() {
  Wire.requestFrom(8, 2);
    //I2C_readAnything(val);
  if (Wire.available()) {
    int val = Wire.read (); 
    val <<= 8; 
    val |= Wire.read ();
    Serial.println(val);
    int led = map(val,0,1023,0,255);
    analogWrite(11, led);
  }
  delay(500);
}

