int pot = A0;

int btn = 2;

bool flag;

void interruptRoutine(void);

void setup()
{
  pinMode(btn, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), interruptRoutine, RISING);
  
  Serial.begin(9600);
}

void loop()
{
  if ( flag )
  {
    Serial.println(analogRead(pot));
    delay(350);
    
    flag = false;
  }
}

void interruptRoutine(void)
{
  flag = true;
}

