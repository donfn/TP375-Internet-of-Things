#include <Servo.h>

Servo SERVO;

int pot = A0;

void setup(void)
{
  SERVO.attach(9);
}

void loop(void)
{
  int angle = map( analogRead(pot), 0, 1023, 0, 180 );
  SERVO.write(angle);
}

