#include <WiFi.h>
#include <PubSubClient.h>

unsigned long last = 0;
const int ledPin = 16;
const int ledPWMpin = 18;
const int potPin = 35;

// Replace with your credentials
const char* ssid = "xxxx";
const char* password = "xxxx";

// Replace with your IP
const char* mqtt_server = "xxx.xxx.xxx.xxx"; 
int mqtt_port = 1883;

String message;
bool state = false;

WiFiClient espClient;
PubSubClient client(espClient);

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup(){
  pinMode(potPin, INPUT); 
  pinMode(ledPWMpin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPWMpin, ledChannel);

  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);   
  Serial.print("Connecting.");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected - IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++){
    message += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(String(topic));
  Serial.print("/");
  Serial.print(String(message));
  Serial.println("] ");
  
  if (String(topic) == "esp32/out"){
    if (message == "on") {
      digitalWrite(ledPin, HIGH);
    }
    else if (message == "off"){
      digitalWrite(ledPin, LOW);
    }
  }
  else if (String(topic) == "esp32/pwm"){
    ledcWrite(0, message.toInt());
  }
  message = "";
}

void reconnect(){
  // Loop until we're reconnected
  while (!client.connected()){
    Serial.println("Attempting MQTT connection...");
    if (client.connect("ESP32 client")){
      Serial.println("Connected");
      client.subscribe("esp32/out");
      client.subscribe("esp32/pwm");
    }
    else{
      Serial.print(client.state());
      Serial.println("Failed - Try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop(){
  if (!client.connected()) {
    reconnect();
  }
  // boolean loop ()
  // This should be called regularly to allow the client to process 
  // incoming messages and maintain its connection to the server.
  client.loop();
  
  if (millis() > last + 250){
    last = millis();
    client.publish("esp32/pot", String(analogRead(potPin)).c_str());
  }
}
