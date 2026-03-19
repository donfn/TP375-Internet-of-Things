//#include <Wire.h>

int potValue = 0;

void setup()
{
  // Εκκίνηση σειριακής θύρας
  Serial.begin(9600);
  //while(!Serial);
  
  // Εκκίνηση I2C με διεύθυνση 127 (τελευταία υποστηριζόμενη)
 // Wire.begin(127);

  // Όταν ληφθεί αίτημα για αποστολή δεδομένων, θα τρέξει το reqEvt()
  //Wire.onRequest(reqEvt); 
}

void loop()
{
  // Λήψη αναλογικής τιμής απ' το Α0 κάθε 100 ms και μετασχηματισμός 
  // από 0...1023 σε 0...255
  potValue = map(analogRead(A0), 0, 1023, 0, 255);
  //Serial.write(potValue); 
  Serial.println(potValue);
  delay(10);
}
