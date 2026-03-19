#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAA
};
IPAddress ip(10, 0, 26, 177);

EthernetServer server(80);

int firsttime = 0;
String clientRequest = "";
int pwmpercent;
int ledstatus;

void setup() {
  pinMode(5, OUTPUT);                       //on/off status of clients led
  pinMode(6, OUTPUT);                       //pwm led sent from clients pot
  Serial.begin(9600);
  Serial.println("Ethernet WebServer Example");
  Ethernet.begin(mac, ip);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  server.begin();
  Serial.print("Server is at: ");
  Serial.println(Ethernet.localIP());
  Serial.println("Ready and waiting");
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("");
    Serial.print("New client with IP ");
    Serial.println(client.remoteIP());
    while (client.connected()) {
      if (client.available()) {
        if (firsttime == 0) {
          Serial.println("Sending respone to browswer/client");
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {             //a0 controls the pwm led on the client
            int sensorReading = analogRead(analogChannel);                              //for the rest of the analogs we do nothing for now
            client.print("analog input ");                                              //just prints them on the browser
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          firsttime = 1;
          break;
        }
      }
    }
    clientRequest = client.readString();
    int setA0 = clientRequest.indexOf("A0=");
    String strsetA0 = clientRequest.substring(setA0 + 3, setA0 + 7);
    int valueA0 = strsetA0.toInt();
    int led = clientRequest.indexOf("LED=");
    String strled = clientRequest.substring(led + 4);
    ledstatus = strled.toInt();
    digitalWrite(5, ledstatus);
    int pwmled = map(valueA0, 0, 1023, 0, 255);                               //mapping for analogWrite
    pwmpercent = map(valueA0, 0, 1023, 0, 100);                               //mapping for serial monitor in percentage
    analogWrite(6, pwmled);
    delay(1);
    Serial.println("");
    Serial.println("Clients request: ");
    Serial.println(clientRequest);
    client.stop();
    Serial.print("PWMled on server controlled from clients A0 = ");
    Serial.print(pwmpercent);
    Serial.println("%");
    Serial.print("on/off led on client is = ");
    Serial.print(ledstatus);
    Serial.println("");
    Serial.println("Client disconnected");
    firsttime = 0;
  }
}
