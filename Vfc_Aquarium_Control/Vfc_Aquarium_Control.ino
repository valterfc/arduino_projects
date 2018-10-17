#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "config.h"
#include "page_index.h"
#include "FS.h"

ESP8266WebServer server(80);


void setup() {
  //BUILTIN_LED = GPIO2 DO ESP8266
  pinMode(BUILTIN_LED, OUTPUT);  //DEFINE O PINO COMO SAÍDA

  Serial.begin(74880);
  WiFi.begin(ssid, password);  //Connect to the WiFi network
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
    delay(500);
    Serial.println("Waiting to connect…");
  }
 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP
 
  server.on("/other", []() {   //Define the handling function for the path
    server.send(200, "text / plain", "Other URL");
  });
 
  server.on("/", handleRootPath);    //Associate the handler function to the path
  server.begin();                    //Start the server
  Serial.println("Server listening");

  digitalWrite(BUILTIN_LED, HIGH); //LED DA PLACA APAGA (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  delay(1000); //INTERVALO DE 1 SEGUNDO

  if (SPIFFS.begin()) {
      Serial.println('file system was mounted successfully');
  }

  Serial.println("varendo diretorios: ");
  Dir dir = SPIFFS.openDir("");
  while (dir.next()) {
      Serial.print(dir.fileName() + ' : ');
      File f = dir.openFile("r");
      Serial.println(f.size());
  }  

/*
  Serial.println("varendo diretorios: /");
  dir = SPIFFS.openDir("/");
  while (dir.next()) {
      Serial.print(dir.fileName());
      File f = dir.openFile("r");
      Serial.println(f.size());
  }  
*/

/*
  Serial.println("varendo diretorios: /data");
  dir = SPIFFS.openDir("/data");
  while (dir.next()) {
      Serial.print("data" + dir.fileName());
      File f = dir.openFile("r");
      Serial.println(f.size());
  }  
*/

  Serial.println('list files end');
}
 
void loop() {
  digitalWrite(BUILTIN_LED, LOW); //LED DA PLACA ACENDE (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  delay(1000); //INTERVALO DE 1 SEGUNDO

  server.handleClient();         //Handling of incoming requests

  //Serial.println("teste");

  digitalWrite(BUILTIN_LED, HIGH); //LED DA PLACA APAGA (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  delay(1000); //INTERVALO DE 1 SEGUNDO
}
 
void handleRootPath() {            //Handler for the rooth path
  //server.send(200, "text/plain", "Hello world");
  server.send(200, "text/html; charset=utf-8", printPageIndex());
}
