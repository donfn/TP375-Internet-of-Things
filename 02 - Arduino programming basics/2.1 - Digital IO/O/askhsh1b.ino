int led = 13;
int btn = 8;

int state;

void setup() {
  
  pinMode(btn, INPUT_PULLUP);
  
  pinMode(led, OUTPUT);
  
}

void loop() {
  
  state = digitalRead(btn);

  digitalWrite(led, !state);
  
}
