int hbridge_in1 = 9;
int hbridge_in2 = 8;

void setup(void)
{
  pinMode(hbridge_in1, OUTPUT);
  pinMode(hbridge_in2, OUTPUT);
}
void loop(void)
{
  digitalWrite(hbridge_in1, HIGH);
  digitalWrite(hbridge_in2, LOW);
  delay(3000);
  
  digitalWrite(hbridge_in1, LOW);
  digitalWrite(hbridge_in2, LOW);
  delay(1000);
  
  digitalWrite(hbridge_in1, LOW);
  digitalWrite(hbridge_in2, HIGH);
  delay(3000);

  digitalWrite(hbridge_in1, HIGH);
  digitalWrite(hbridge_in2, HIGH);
  delay(1000);
}
