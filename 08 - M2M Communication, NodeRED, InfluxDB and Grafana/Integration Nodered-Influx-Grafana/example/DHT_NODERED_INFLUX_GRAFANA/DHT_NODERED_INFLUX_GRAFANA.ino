#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* ssid = "xxxx";
const char* password = "xxxx";

// Replace with your IP
const char* mqtt_server = "xxx.xxx.xxx.xxx"; 
int mqtt_port = 1883;

unsigned long last = 0;

const int dhtPin = 21; 
String message;
bool state = false;

WiFiClient espClient;
PubSubClient client(espClient);

#define DHTTYPE DHT11
DHT dht(dhtPin, DHTTYPE);

void setup(){
  
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
}

void reconnect(){
  while (!client.connected()){
    Serial.println("Attempting MQTT connection...");
    if (client.connect("ESP32 client")){
      Serial.println("Connected");
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
  
  if (millis() > last + 10000){
    last = millis();

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    
  char payload[50];
  snprintf(payload, sizeof(payload), "{\"temperature\": %.2f, \"humidity\": %.2f}", t, h);

  client.publish("esp32/dht11", payload);
  }
}
