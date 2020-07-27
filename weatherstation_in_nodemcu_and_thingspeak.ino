#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#include <TinyGPS++.h>

#define SEALEVELPRESSURE_HPA (1013.25)

char ssid[] = "";   // your network SSID (name) 
char pass[] = "";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 1106607;
const char * myWriteAPIKey = "U7JNG14Q3FIEB1SK";

int number = 0;
int x;


Adafruit_BME280 bme;

float temperature, humidity, pressure, altitude;


TinyGPSPlus gps;


void setup() {
  Serial.begin(115200);  // Initialize serial

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  bme.begin(0x76);
}

void loop() {
  temperature = bme.readTemperature();
  number=temperature;
  ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);
  humidity = bme.readHumidity();
  number=humidity;
  ThingSpeak.writeField(myChannelNumber, 2, number, myWriteAPIKey);
  pressure = bme.readPressure() / 100.0F;
  number=pressure;
  ThingSpeak.writeField(myChannelNumber, 3, number, myWriteAPIKey);
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  number=altitude;
  ThingSpeak.writeField(myChannelNumber, 4, number, myWriteAPIKey);


  while (Serial.available() > 0){
    gps.encode(Serial.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      number=gps.location.lat();
      ThingSpeak.writeField(myChannelNumber, 5, number, myWriteAPIKey);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
      number=gps.location.lng();
      x =ThingSpeak.writeField(myChannelNumber, 6, number, myWriteAPIKey);
    }
  }
  
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    //Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  
  
  delay(20000); // Wait 20 seconds to update the channel again
}
