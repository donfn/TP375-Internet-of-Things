#include <Stepper.h>

int steps = 2038;

Stepper STEPPER(steps, 8, 9, 10, 11);

void setup()
{
  STEPPER.setSpeed(10);
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Clockwise.");
  STEPPER.step(steps);
  delay(500);

  Serial.println("Counter-clockwise.");
  STEPPER.step(-steps);
  delay(500);
}

