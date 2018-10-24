/**
   Vfc AquaControl by ValterFC
   https://github.com/valterfc
   
   https://github.com/valterfc/arduino_projects/tree/master/Vfc_AquaControl

   This code is released to the "Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0)"
   http://creativecommons.org/licenses/by-nc/3.0/
*/

#include <ESP8266WiFi.h>

#include "ota_update.h"
#include "config.h" //copy "config.example.h" to "config.h" and edit it
#include "mqtt_client.h"
#include "web_server.h"

//BUILTIN_LED - GPIO2 - inverted signal
const int LED_OFF = HIGH;
const int LED_ON = LOW;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
  //BUILTIN_LED = GPIO2 DO ESP8266
  pinMode(BUILTIN_LED, OUTPUT); //set BUILTIN_LED as output

  //init serial communication
  Serial.begin(74880); //for me, it´s better speed; you can change this to 115200
  Serial.println("booting");

  //init wifi
  initWiFi();

  //setup OTA update
  ota_setup();

  //webserver setup
  webserver_setup();

  digitalWrite(BUILTIN_LED, LED_OFF); //builtin LED OFF (inverse logic sign for PIN 2)
  delay(1000); //INTERVALO DE 1 SEGUNDO

  //MQTT Mosquitto Setup
  mqtt_setup();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {
  //do ota update
  ota_handle();
  
  //digitalWrite(BUILTIN_LED, LED_ON); //builtin LED ON (inverse logic sign for PIN 2)
  //delay(1000); //1 second interval

  reconnectWiFi();
  webserver_handleClient();
  mqtt_handleClient();

  //digitalWrite(BUILTIN_LED, LED_OFF); //builtin LED OFF (inverse logic sign for PIN 2)
  //delay(1000); //1 second interval
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void initWiFi() {
  //hostname
  WiFi.hostname("esp8266_aquacontrol");
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.printf("New hostname: %s\n", WiFi.hostname().c_str());
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void reconnectWiFi() {
    //if you are already connected to the WI-FI network, nothing is done.
    //Otherwise connection attempts are made
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(ssid, password); //Connect to the WiFi network
     
    Serial.print("Waiting to connect");
    while (WiFi.status() != WL_CONNECTED) //Wait for connection
    {
        delay(500);
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
