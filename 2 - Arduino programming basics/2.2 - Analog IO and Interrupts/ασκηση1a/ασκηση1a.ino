int ld1 = 13;
int ld2 = 12;

int btn = 2;

int state = LOW;

void setup() {
  
  pinMode(btn, INPUT_PULLUP);
  pinMode(ld1, OUTPUT);
  pinMode(ld2, OUTPUT);
    
}

void loop() {
  
  if ( !digitalRead(btn) )
  {
    digitalWrite(ld1, HIGH);
  }
  else
  {
    digitalWrite(ld1, LOW);
  }
  
  digitalWrite(ld2, state);

  state = !state; 

  delay(5000);
  
}
