int btn = 2;

int buz = 3;

bool flag;

void interruptRoutine(void);

void setup(void)
{
  pinMode(btn, INPUT_PULLUP);
  pinMode(buz, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2), interruptRoutine, FALLING);  
}

void loop(void)
{
  if ( flag ) 
  {
    tone(buz, 1000, 200);
    delay(400);
  
    tone(buz, 1500, 300);
    delay(400);
  
    tone(buz, 2000, 400);

    flag = false;
  }
}
void interruptRoutine(void)
{
  flag = true;
}
