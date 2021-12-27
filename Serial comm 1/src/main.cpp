#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"   
 #include <Adafruit_Sensor.h>
#include<SoftwareSerial.h>
SoftwareSerial SUART(4, 5); 

float t, h;

int ENA = 14;

int IN1 = 0;

int IN2 = 2;

char x;
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}


void Speedcontrol() {

  digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);

while(x<=10)
{
  analogWrite(ENA, LOW);
  Serial.println("FAN OFF");
}

while(x<=15 && x>10)
{
  analogWrite(ENA,50);
  Serial.println("FAN SPEED 1");
}

while(x<=20 && x>15)
{
  analogWrite(ENA, 100);
  Serial.println("FAN SPEED 2");
}

while(x<=25 && x>20)
{
  analogWrite(ENA, 150);
  Serial.println("FAN SPEED 3");
}

while(x<=30 && x>20)
{
  analogWrite(ENA, 175);
  Serial.println("FAN SPEED 4");
}

while(x>30){
  analogWrite(ENA, HIGH);
  Serial.println("FAN SPEED MAX");
}

digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
}

void setup() {
Serial.begin(9600);
WiFiManager wifiManager;
wifiManager.setAPCallback(configModeCallback);
pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
if(!wifiManager.autoConnect()) {
Serial.println("failed to connect and hit timeout");
 ESP.reset();
 delay(1000);
}
Serial.println("connected to network :)");
SUART.begin(9600);
}

void loop() {
 byte n = SUART.available(); 
  if (n != 0)
  {
     x = SUART.read();  
    Serial.println(x);       
    Speedcontrol();
  }

}