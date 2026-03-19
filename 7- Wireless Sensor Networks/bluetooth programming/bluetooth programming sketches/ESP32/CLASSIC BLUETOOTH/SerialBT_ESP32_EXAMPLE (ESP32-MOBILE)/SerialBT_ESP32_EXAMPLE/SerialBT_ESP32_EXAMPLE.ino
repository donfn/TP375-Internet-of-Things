// Εισαγωγή βιβλιοθήκης
#include "BluetoothSerial.h"

// Δημιουργία αντικειμένου
BluetoothSerial SerialBT;

// Δήλωση μεταβλητών και pin
char input;
unsigned long previous = 0;
int led = 26;
const int potPin = 34;
int potValue = 0;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32Test");
  Serial.print("The device started, now you can pair it with bluetooth");
}

void loop(){
  // Ελέγχει αν είναι διαθέσιμη η SerialBT
  if (SerialBT.available()){
    // Διαβάζει δεδομένα από την Android συσκευή
    input = SerialBT.read();
    if (input == '1'){
      Serial.println("HIGH");
      digitalWrite(led, HIGH);
      SerialBT.println("The LED is now ON");
    }
    if (input == '0'){
      digitalWrite(led, LOW);
      SerialBT.println("The LED is now OFF");
      Serial.println("LOW");
    }
  }    
  if (millis() > previous + 1000)
  {
    previous = millis();
    potValue = analogRead(potPin);
    SerialBT.print("Potentiometer Value = ");
    SerialBT.println(potValue);
  } 
}
