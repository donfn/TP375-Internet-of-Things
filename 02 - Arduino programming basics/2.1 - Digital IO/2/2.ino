int led = 13;
int btn = 8;

int state = 0;



void setup() {
  
  pinMode(btn, INPUT_PULLUP);
  
  pinMode(led, OUTPUT);
  
}

void loop() {
  
  if ( digitalRead(btn) == 0 )
  {
    state = !state;
  }
  
  digitalWrite(led, state);
  delay(250);

}
