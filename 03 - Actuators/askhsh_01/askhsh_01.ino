int button = 12;
int relay = 10;

void setup(void)
{
  pinMode(button, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
}
void loop(void)
{
  if ( !digitalRead(button) )
  {
    digitalWrite(relay, HIGH);
  }
  else
  {
    digitalWrite(relay, LOW);
  }
}

