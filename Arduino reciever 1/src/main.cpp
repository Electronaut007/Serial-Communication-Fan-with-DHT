#include <Arduino.h>
 #include <Adafruit_Sensor.h>
#include "DHT.h"
#include<SoftwareSerial.h>
SoftwareSerial SUART(2, 3); 
#define DHTPIN A0
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);
float temperature;

void setup()
{
  Serial.begin(9600);
  SUART.begin(9600);

}

void loop()
{
  
  temperature = dht.readTemperature();
  Serial.print("Temperature = "); Serial.print((int)temperature); Serial.print(" degC");
  Serial.println("");
  SUART.print('<');                 
  SUART.print((int)temperature,DEC);
  SUART.print('>');
  SUART.println();

  delay(1000);
}