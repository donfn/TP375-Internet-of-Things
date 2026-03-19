int ld1 = 13;
int ld2 = 12;

int btn = 2;

int state1 = LOW;
int state2 = LOW;

void setup()
{
  pinMode(btn, INPUT_PULLUP);
  pinMode(ld1, OUTPUT);
  pinMode(ld2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), lightLED, FALLING);
}

void loop()
{
  digitalWrite(ld1, state1);
  state1 = !state1;
  delay(5000);
}

void lightLED(void)
{
  digitalWrite(ld2, state2);
  state2 = !state2;
}

