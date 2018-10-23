#include "ESP8266WiFi.h"

#include "config.h" //copy "config.example.h" to "config.h" and edit it
#include "mqtt_client.h"
#include "web_server.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
  //BUILTIN_LED = GPIO2 DO ESP8266
  pinMode(BUILTIN_LED, OUTPUT);  //DEFINE O PINO COMO SAÍDA

  //init serial communication
  Serial.begin(74880);

  //init Wifi
  initWiFi();

  //webserver setup
  webserver_setup();

  digitalWrite(BUILTIN_LED, HIGH); //LED DA PLACA APAGA (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  delay(1000); //INTERVALO DE 1 SEGUNDO

  //MQTT Mosquitto Setup
  mqtt_setup();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {
  //digitalWrite(BUILTIN_LED, LOW); //LED DA PLACA ACENDE (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  //delay(1000); //INTERVALO DE 1 SEGUNDO

  initWiFi();
  webserver_handleClient();
  mqtt_handleClient();

  //digitalWrite(BUILTIN_LED, HIGH); //LED DA PLACA APAGA (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  //delay(1000); //INTERVALO DE 1 SEGUNDO
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void initWiFi()
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
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
