#include "CapacitiveSensor.h"

CapacitiveSensor cs_4_2 = CapacitiveSensor(25, 26); // sensor pin 25 

void setup() {
    cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
    Serial.begin(9600);

}

void loop() {

    long start = millis();
    long total1 = cs_4_2.capacitiveSensor(30);

    Serial.print(millis() - start);
    Serial.print("\t");
    Serial.print(total1 );
    Serial.print("\n");
    delay(10);
}
