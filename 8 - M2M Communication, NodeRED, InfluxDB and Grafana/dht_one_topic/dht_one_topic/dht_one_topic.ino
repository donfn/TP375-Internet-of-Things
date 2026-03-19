#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* ssid = "microelectronics";
const char* password = "microelectronics2018";

// Replace with your IP
const char* mqtt_server = "xxx.xxx.xxx.xxx"; 
int mqtt_port = 1883;

unsigned long last = 0;
const int ledPin = 16;
const int ledPWMpin = 18;
const int dhtPin = 21; 
String message;
bool state = false;

WiFiClient espClient;
PubSubClient client(espClient);

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

#define DHTTYPE DHT11
DHT dht(dhtPin, DHTTYPE);

void setup(){
  pinMode(ledPWMpin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPWMpin, ledChannel);

  Serial.begin(115200);

  dht.begin();

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
    ledcWrite(ledChannel, message.toInt());
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

  client.loop();
  
  if (millis() > last + 2000){
    last = millis();

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    
    String metrics = "TEMP" + String(t) + "HUM" + String(h);

    client.publish("esp32/temphum", metrics.c_str());
  }
}
