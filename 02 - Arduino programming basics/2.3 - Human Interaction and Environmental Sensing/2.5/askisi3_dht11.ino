#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT DHT(DHTPIN, DHTTYPE);

const byte heat = 13;
//const byte cool = 12;
const byte dehm = 11;

const byte heat_lo_threshold = 22;
const byte heat_hi_threshold = 25;
//const byte cool_lo_threshold = 20;
//const byte cool_hi_threshold = 22;
const byte dehm_lo_threshold = 50;
const byte dehm_hi_threshold = 55;

bool heat_flag;
//bool cool_flag;
bool dehm_flag;

void setup() {
  Serial.begin(9600);
  DHT.begin();
  delay(2000);
}

void loop() {
  
  float hmd = DHT.readHumidity();

  float tmp = DHT.readTemperature();

  if ( isnan(hmd) || isnan(tmp) )
  {
    return;
  }

  if ( tmp < heat_lo_threshold ) 
  {
    digitalWrite(heat, HIGH);
    heat_flag = true;
  }
  else if ( tmp > heat_hi_threshold)
  {
    digitalWrite(heat, LOW);
    heat_flag = false;
  }

  //if ( tmp > cool_hi_threshold )
  //{
 //   digitalWrite(cool, HIGH);
  //  cool_flag = true;
//  }
 // else if ( tmp < cool_lo_threshold )
 // {
  //  digitalWrite(cool, LOW);
  //  cool_flag = false;
 // }

  if ( hmd > dehm_hi_threshold )
  {
    digitalWrite(dehm, HIGH);
    dehm_flag = true;
  }
  else if ( hmd < dehm_lo_threshold )
  {
    digitalWrite(dehm, LOW);
    dehm_flag = false;
  }
    
  Serial.print("Humidity: ");
  Serial.print(hmd);
  Serial.print(" % Temperature: ");
  Serial.print(tmp);
  Serial.print(" C ");

  if ( heat_flag )
    Serial.print("Currently heating...\r\n");
 // if ( cool_flag )
 //   Serial.print("Currently cooling...\r\n");
  if ( dehm_flag )
    Serial.print("Currently dehumidifying...\r\n");  

  delay(2000);
}
