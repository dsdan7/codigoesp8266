
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureBearSSL.h>
#define pinSensor 2
#define pinLed 5

ESP8266WiFiMulti WiFiMulti;

const char* ssid = "alarme";
const char* password = "ovofrito123";

//Your Domain name with URL path or IP address with path
const char* serverName = "https://reprisebackend-production.up.railway.app/api/tutorials";
unsigned long espera;
int estado = 0;
 void setup() {
  pinMode(pinSensor,INPUT);
  pinMode(pinLed,OUTPUT); 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;
 int sensor;
 sensor = digitalRead(pinSensor);

  if (sensor == LOW)
 {

      https.begin(*client,serverName);
      https.addHeader("Content-Type", "application/json");
      int httpResponseCode = https.POST("{\"title\":\"ALARME ATIVADO\",\"description\":\"MOVIMENTO DETECTADO\"}");
      String payload = https.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.println(payload);
      https.end();
   Serial.println("objeto detectado");
   digitalWrite(pinLed,HIGH);
   delay(3000);
   estado = 1; 
  }
   else  if(sensor == HIGH)
 {
    
    digitalWrite(pinLed,LOW);
    estado = 2 ;
 }
  
}
