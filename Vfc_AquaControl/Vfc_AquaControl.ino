#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "config.h" //copy "config.example.h" to "config.h" and edit it
#include "FS.h"

ESP8266WebServer server(80);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

  //init filesystem
  if (SPIFFS.begin()) {
      Serial.println('file system was mounted successfully');
  }

 
  //**
  //* rotes
  //* use "https://github.com/esp8266/arduino-esp8266fs-plugin" to upload files to ESP8266 SPIFFS
  //**
  //Associate the handler function to the path
  //server.on("/", handleRootPath);
  server.on("/", []() {
    File_Download("/index_minify.html");
  });
  server.on("/files/vfcaquacontrol.png", []() {
    File_Download("/files/vfcaquacontrol.png");
  });
  server.on("/files/manifest.json", []() {
    File_Download("/files/manifest.json");
  });

  server.on("/files/icons/icon-16x16.png", []() {
    File_Download("/files/icons/icon-16x16.png");
  });
  server.on("/files/icons/icon-32x32.png", []() {
    File_Download("/files/icons/icon-32x32.png");
  });
  server.on("/files/icons/icon-72x72.png", []() {
    File_Download("/files/icons/icon-72x72.png");
  });
  server.on("/files/icons/icon-96x96.png", []() {
    File_Download("/files/icons/icon-96x96.png");
  });
  server.on("/files/icons/icon-128x128.png", []() {
    File_Download("/files/icons/icon-128x128.png");
  });
  server.on("/files/icons/icon-144x144.png", []() {
    File_Download("/files/icons/icon-144x144.png");
  });
  server.on("/files/icons/icon-152x152.png", []() {
    File_Download("/files/icons/icon-152x152.png");
  });
  server.on("/files/icons/icon-192x192.png", []() {
    File_Download("/files/icons/icon-192x192.png");
  });
  server.on("/files/icons/icon-256x256.png", []() {
    File_Download("/files/icons/icon-256x256.png");
  });
  server.on("/files/icons/icon-384x384.png", []() {
    File_Download("/files/icons/icon-384x384.png");
  });
  server.on("/files/icons/icon-512x512.png", []() {
    File_Download("/files/icons/icon-512x512.png");
  });

  server.begin();                    //Start the server
  Serial.println("Server listening");

  digitalWrite(BUILTIN_LED, HIGH); //LED DA PLACA APAGA (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  delay(1000); //INTERVALO DE 1 SEGUNDO

/*
  //listing the directory files
  Serial.println("listing the directory files");
  Dir dir = SPIFFS.openDir("");
  while (dir.next()) {
      Serial.print(dir.fileName());
      Serial.print(" - ");
      File f = dir.openFile("r");
      Serial.println(f.size());
  }  
*/
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {
  digitalWrite(BUILTIN_LED, LOW); //LED DA PLACA ACENDE (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  delay(1000); //INTERVALO DE 1 SEGUNDO

  server.handleClient();         //Handling of incoming requests

  //Serial.println("teste");

  digitalWrite(BUILTIN_LED, HIGH); //LED DA PLACA APAGA (ACIONAMENTO COM SINAL LÓGICO INVERSO PARA O PINO 2)
  delay(1000); //INTERVALO DE 1 SEGUNDO
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void File_Download(String fileName) { // This gets called twice, the first pass selects the input, the second pass then processes the command line arguments
  SPIFFS_file_download(fileName);
  
  //to download file with args
  //if (server.args() > 0 ) { // Arguments were received
  //  if (server.hasArg("files")) SPIFFS_file_download(server.arg(0));
  //}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void SPIFFS_file_download(String filename){
  File download = SPIFFS.open(filename, "r");
  if (download) {
    //content type
    String contentType = "text/html; charset=utf-8";
    if ( fileExt(filename, "png") ) {
      contentType = "image/png";
    } else if ( fileExt(filename, "jpg") || fileExt(filename, "jpeg") ) {
      contentType = "image/jpeg";
    } else if ( fileExt(filename, "json") ) {
      contentType = "application/json; charset=UTF-8";
    } else if ( fileExt(filename, "xml") ) {
      contentType = "application/xml; charset=UTF-8";
    } else if ( fileExt(filename, "htm") || fileExt(filename, "html") ) {
      contentType = "text/html; charset=utf-8";
    } else {
      contentType = "text/html; charset=utf-8";
    }

    //to make download
    /*
    server.sendHeader("Content-Type", "text/text");
    server.sendHeader("Content-Disposition", "attachment; filename="+filename);
    server.sendHeader("Connection", "close");
    server.streamFile(download, "application/octet-stream");
    */

    //to load file inline
    //server.sendHeader("Content-Type", "text/text");
    server.sendHeader("Content-Disposition", "inline");
    //server.sendHeader("Connection", "close");
    server.streamFile(download, contentType);

    download.close();
  } else ReportFileNotPresent("download"); 
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
String PROGMEM makePageHtml(String bodyTXT) {
  return String("<!DOCTYPE html>")+
          "<html lang='en'> "+
          "<head> "+
          "  <meta charset='UTF-8'> "+
          " <meta name='viewport' content='width=device-width, initial-scale=1.0'> "+
          " <meta http-equiv='X-UA-Compatible' content='ie=edge'> "+
          " <title>Document</title> "+
          "</head> "+
          "<body> "+
          " \r\n "+bodyTXT+" \r\n"
          "</body> "+
          "</html>";
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ReportFileNotPresent(String target){
  String html = makePageHtml("<h3> '"+target+"' not found</h3>");
  server.send(404, "text/html; charset=utf-8", html);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool fileExt(String filename, String extension) {
  filename.toLowerCase();
  return filename.endsWith(extension);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void handleRootPath() {            //Handler for the rooth path
//  server.send(200, "text/html; charset=utf-8", makePageIndex());
//}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//String PROGMEM makePageIndex() {
//  return String("<html></html>"); //your minify page html
//}
