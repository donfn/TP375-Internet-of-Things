//#include <Wire.h>

int value;

void setup()
{
  pinMode(11, OUTPUT);
  // Εκκίνηση σειριακής θύρας
  Serial.begin(9600);
  //while(!Serial);
  // Εκκίνηση I2C ΧΩΡΙΣ διεύθυνση σημαίνει ότι θεωρούμε αυτή
  // τη συσκευή MASTER στο δίαυλο

}

void loop()
{
  // Αίτηση για 1 byte από τη συσκευή 127

  // Εάν έχουμε λάβει bytes...
  if(Serial.available())
  {
    // ...τα διαβάζουμε
    value = Serial.parseInt();
    //Serial.println(value);
    // Εκτύπωση στη σειριακή
    //Serial.println(value);
    // Η τιμή είναι ΉΔΗ κατάλληλη για PWM (το map() το κάνει
    // η slave συσκευή)
    analogWrite(11, value);
    delay(10);
  }
  
}
