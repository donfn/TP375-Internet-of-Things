///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////     CLIENT CODE     /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server(10, 0, 26, 177);                //webserver to connect

IPAddress ip(10, 0, 26, 178);                     //manual ip address should dhcp fail 
IPAddress myDns(10, 0, 26, 1);                    //dhcp server

EthernetClient client;

bool ledstatus = LOW;

void setup() {
  pinMode(7, INPUT_PULLUP);                     //button to control on/off led on client
  pinMode(6, OUTPUT);                          //pwm led controlled fro m webserver A0
  pinMode(5, OUTPUT);                         //on/off led on client
  Serial.begin(9600);
  Serial.println("Ethernet WebClient Example");
  Serial.println("Initialising Ethernet with DHCP, please wait");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");                              
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {              // Check for Ethernet hardware present
      Serial.println("No Ethernet shield. Can't run without hardware. :(");
      while (true) {
        delay(1);                         // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    Ethernet.begin(mac, ip, myDns);                       // try to congifure using IP address instead of DHCP:
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  delay(1000);                                            // give the Ethernet shield a second to initialize:
  Serial.println("Ready and waiting");
}

void loop() {
  int pin = digitalRead(7);
  if (pin == LOW) {                                         //if button pressed change the status of the on/off led
    ledstatus = !ledstatus;                                 // and request from server pwm for the other led.
    digitalWrite(5, ledstatus);                             // along with the request we will send the status of the on/off led and A0 pot reading
    Serial.println("Requesting from webserver");
    Serial.println("");
    delay(2000);
    getinfo();
  }
}


void getinfo() {
  int a0 = analogRead(A0);
  if (client.connect(server, 80)) {
    String query = (String)"GET /arduino/setA0=" + a0 + "&LED=" + ledstatus + " HTTP/1.1";        //http1.1 request with clients a0 value and on/off led status
    Serial.print("Connected to ");
    Serial.println(client.remoteIP());
    Serial.print("Sending request: ");
    Serial.println(query);
    client.println(query);
    client.println("User-Agent: Arduino");
    client.print("Host: ");
    client.println(Ethernet.localIP());
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Connection failed");
  }
  delay(1);        //must have eidalos den douleyei
  String response = client.readString();                                        //receiving response from server in a string format
  int setA0 = response.indexOf("analog input 0 is ");                           //searching for a0 value from server to light the pwm led
  String strsetA0 = response.substring(setA0 + 18, setA0 + 22);
  int valueA0 = strsetA0.toInt();                                               //string to int the value of a0
  int pwmled = map(valueA0, 0, 1023, 0, 255);                                   //mapping for analogWrite
  int pwmpercent = map(valueA0, 0, 1023, 0, 100);                               //mapping for serial monitor in percentage
  analogWrite(6,pwmled);
  Serial.println("");
  Serial.println("Response from server: ");
  Serial.println(response);                                                   //servers response printed in serial monitor
  Serial.println();
  Serial.println("Disconnecting.");
  Serial.print("PWMled on client controlled from servers A0 = ");
  Serial.print(pwmpercent);
  Serial.println("%");
  Serial.println("");
  client.stop();                                                              //disconnecting from server
}
