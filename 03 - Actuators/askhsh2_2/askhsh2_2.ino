int motor1 = 9;
int motor2 = 8;

void setup(void)
{
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
}
void loop(void)
{
  digitalWrite(motor2, LOW); 
  for (int i = 0 ; i <= 255; i += 5)
  {
    analogWrite(motor1, i);
    delay(500);
  }

  for (int i = 255 ; i >= 0; i -= 5)
  {
    analogWrite(motor1, i);
    delay(500);
  }

  digitalWrite(motor1, LOW);
  for (int i = 0 ; i <= 255; i += 5)
  {
    analogWrite(motor2, i);
    delay(500);
  }

  for (int i = 255 ; i >= 0; i -= 5)
  {
    analogWrite(motor2, i);
    delay(500);
  }
}
