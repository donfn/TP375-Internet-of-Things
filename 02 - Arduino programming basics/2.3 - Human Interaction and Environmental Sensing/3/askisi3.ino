const byte heat = 11;
const byte cool = 10;

const byte heatL = 22;
const byte heatH = 25;

const byte coolL = 20;
const byte coolH = 22;

bool heat_flag;
bool cool_flag;

int sensorValue;
double temp;

void setup()
{
  Serial.begin(9600);
}

void loop() {
  
  sensorValue = analogRead(A0);        //read the analog sensor and store it
  temp = (double)sensorValue / 1024;   //find percentage of input reading
  temp = temp * 5;                     //multiply by 5V to get voltage
  temp = temp - 0.5;                   //Subtract the offset 
  temp = temp * 100;
 
  if ( temp < heatL ) 
  {
    digitalWrite(heat, HIGH);
    heat_flag = true;
  }
  else if ( temp > heatH)
  {
    digitalWrite(heat, LOW);
    heat_flag = false;
  }

  if ( temp > coolH )
  {
    digitalWrite(cool, HIGH);
    cool_flag = true;
  }
  else if ( temp < coolL )
  {
    digitalWrite(cool, LOW);
    cool_flag = false;
  }
  Serial.print(" % Temperature: ");
  Serial.print(temp);
  Serial.print(" C ");

  if ( heat_flag )
    Serial.print("Currently heating...\r\n");
  if ( cool_flag )
    Serial.print("Currently cooling...\r\n"); 

  delay(2000);
}
