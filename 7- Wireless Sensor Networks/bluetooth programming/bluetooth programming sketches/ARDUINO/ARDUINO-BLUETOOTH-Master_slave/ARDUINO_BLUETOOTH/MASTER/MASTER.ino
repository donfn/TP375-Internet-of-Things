#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10,11);

int state = 0;
const int ledPin = 7;
const int buttonPin = 8;
int buttonState = 1;

void setup()
{
  BTSerial.begin(38400);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  if(BTSerial.available() >0)
  {
    state = BTSerial.read();
  }

  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW)
  {
    BTSerial.write('1');
  }
  else
  {
    BTSerial.write('0');
  }

  if (state == '1')
  {
    digitalWrite(ledPin, HIGH);
    state = 0;
  }
  else if (state =='0')
  {
    digitalWrite(ledPin, LOW);
    state = 0;
  }
}
