int pot = A0;
int led = 11;
int potValue;
int pwmValue;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  potValue=analogRead(pot);
  pwmValue = map(analogRead(pot), 0, 1023, 0, 255);

  analogWrite(led, pwmValue);
  Serial.println(potValue); 
  Serial.println(pwmValue); 
}
