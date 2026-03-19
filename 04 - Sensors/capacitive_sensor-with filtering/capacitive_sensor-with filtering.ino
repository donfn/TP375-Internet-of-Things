#include "CapacitiveSensor.h"
#include <RunningMedian.h>

CapacitiveSensor cs_4_2 = CapacitiveSensor(25, 26); // sensor pin 25 
RunningMedian samples = RunningMedian(5);

void setup() {
    //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
    Serial.begin(9600);

}

void loop() {

    long start = millis();
    long total1 = cs_4_2.capacitiveSensor(30);
    samples.add(total1);
    long m = samples.getMedian();
    long a = samples.getAverage();

    Serial.print("median - ");
    Serial.print(m);
    Serial.print("\t");
    Serial.print("average - ");
Serial.print(a);
Serial.print("\n");
    
    delay(10);
}
