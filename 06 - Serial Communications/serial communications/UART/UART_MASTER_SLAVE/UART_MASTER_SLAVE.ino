int button = 7; 
int LED = 8;
char message; // message character 

void setup() {
  Serial.begin(9600); // start communication 
  pinMode(button, INPUT); // input button 1 
  pinMode(LED, OUTPUT); // input button 2
}

void loop() {
  
digitalWrite(LED,LOW); 

if (Serial.available()) // while message received 
  {
    message = Serial.read(); // read message 
    if (message == '1')     // if the message contain character one 
    {
      digitalWrite(LED, HIGH); // switch led one ON 
    }
  }
  
if (digitalRead(button)==HIGH) // while button is pushed 
{
  Serial.write('1');     // send this Character  
}

delay(20); // delay before sending next message 
}
