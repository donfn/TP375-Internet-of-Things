const byte irs = 7;
const byte buz = 3;

void setup(void)
{
  pinMode(buz, OUTPUT);
}

void loop(void)
{
  if ( !digitalRead(irs) )
    tone(buz, 2000);
  else
    noTone(buz);
    
  delay(100);
}
