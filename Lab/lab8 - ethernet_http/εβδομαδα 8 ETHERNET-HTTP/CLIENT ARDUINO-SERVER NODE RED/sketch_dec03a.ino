#include <SPI.h>
#include <String.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0xAA, 0xBA };

IPAddress ip ( 192, 168, 2, 135 );        //arduino ip
IPAddress server ( 192, 168, 2, 3 );      //node-red ip
IPAddress myDns(192, 168, 2, 1);          //my routers ip

EthernetClient client;

void setData();
void ledtoggle();
void getslider();

int ledState = LOW;
int buttonState;
int lastButtonState = LOW;
int ledStateinfo = 0;
String ledsts = "off";
String response;

unsigned long last = 0;
byte BTN2 = 3;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(BTN2, INPUT_PULLUP);      //led toggling button
  pinMode(5, OUTPUT);           //led on/off
  pinMode(6, OUTPUT);           //pwm controlled led
  Serial.begin(9600);
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {                  // Check for Ethernet hardware presence
      Serial.println("Ethernet shield was not found.");
      Serial.println("Try resetting");
      while (true) {
        delay(1);                                                  //do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    Ethernet.begin(mac, ip, myDns);                               // try to congifure using IP address instead of DHCP:
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  delay(1000);                                                  // give the Ethernet shield a second to initialize:
  Serial.println("Ready and waiting for loop");
}

void loop()
{
  bool btn2pressed = digitalRead(BTN2);
  if (btn2pressed == LOW)ledtoggle();                         //if on/off button pressed call ledtoggle()
  if ((millis() - last) > 2000) {                            //every 2000ms get from node-red, slider data and switch status
    last = millis();                                          //by calling getslider()
    getslider();
    Ethernet.maintain();
  }
}

void getslider()                                        //send A0 to node red and with the response we will receive led status(or command)and slider value 
{
  client.stop();
  client.connect(server, 1880);
  int pot = analogRead(A0);
  if ( client.connected() )
  {
    String query = "GET /arduino?pot=" + String(pot)+" HTTP/1.1";           //GET with pot value
    client.println(query);
    client.println("User-Agent: Arduino");
    client.print("Host: ");
    client.println(Ethernet.localIP());                       // Ethernet.localIP() is arduinos ip
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println("client not connected.");
  }
  delay(1);
  response = client.readString();                   //reading response fron node red
  Serial.print(response);
  Serial.println();
  setData();                                      //setData() for manipulating received response
}


void ledtoggle()
{
  int reading = digitalRead(BTN2);               //led toggling with debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ledState = !ledState;
        ledStateinfo = 0;
      }
    }
  }
  if (ledStateinfo == 0) {                    //turning led on or off accordingly
    if (ledState == LOW) {
      ledsts = "on";
      ledStateinfo = 1;
    } else if (ledState == HIGH) {
      ledsts = "off";
      ledStateinfo = 1;
    }
    lastButtonState = reading;
    digitalWrite(5, ledState);
    client.stop();
    client.connect(server, 1880);                           //sending to node red A0 value and led status
    int pot = analogRead(A0);
    if ( client.connected() )
    {
      Serial.println("client is connected.");
      String query = "GET /arduino?pot=" + String(pot) + "&ledstatus=" + String(ledsts)+" HTTP/1.1";
      client.println(query);
      client.println("User-Agent: Arduino");
      client.print("Host: ");
      client.println(Ethernet.localIP());
      client.println("Connection: close");
      client.println();
    }
    else
    {
      Serial.println("client not connected.");
    }
    delay(1);
    response = client.readString();         //reading response fron node red
    setData();                              //setData() for manipulating received response
  }
}


void setData()                                //setData() for manipulating received response
{
  int strlength = response.length();
  String strled = response.substring(strlength - 3, strlength);       //ignoring response except for the last 3 chars of the string
  if (strled.indexOf("off") >= 0) {                                     //if the last 3 chars contain the string "off" then ....
    ledState = LOW;
    ledStateinfo = 0;
    digitalWrite(5, ledState);
  } else if (strled.indexOf("on") >= 0) {                               //else if the last 3 chars contain the string "on" then ....
    ledState = HIGH;
    ledStateinfo = 0;
    digitalWrite(5, ledState);
  } else {                                                          //if none of the above then the last 3 chars are the slider value
    int led = strled.toInt();                                       //convert it to integer
    led = map(led, 0, 100, 0, 255);
    analogWrite(6, led);
  }
  response = "";                                                //clear string response and string strled
  strled = "";
}
