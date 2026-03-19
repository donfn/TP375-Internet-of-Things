#include <Wire.h>

int value;

void setup()
{
  pinMode(11, OUTPUT);
  
  // Εκκίνηση σειριακής θύρας
  Serial.begin(9600);
  while(!Serial);

  // Εκκίνηση I2C ΧΩΡΙΣ διεύθυνση σημαίνει ότι θεωρούμε αυτή
  // τη συσκευή MASTER στο δίαυλο
  Wire.begin();
}

void loop()
{
  // Αίτηση για 1 byte από τη συσκευή 127
  Wire.requestFrom(127, 1);

  // Εάν έχουμε λάβει bytes...
  if (Wire.available())
  {
    // ...τα διαβάζουμε
    value = Wire.read ();

    // Εκτύπωση στη σειριακή
    Serial.println(val);

    // Η τιμή είναι ΉΔΗ κατάλληλη για PWM (το map() το κάνει
    // η slave συσκευή)
    analogWrite(11, val);

  }
  
  delay(500);
}
