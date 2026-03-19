int trig = 13;
int echo = 12;

void setup(void)
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);
}

void loop(void)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);

  int distance = duration / 29 / 2;

  Serial.print( "Distance: " + String(distance) + "cm.\r\n" );

  delay(250);
}
