#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "config.h"
#include "page_index.h"
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
  //**
/*  for (int i =0; i< sizeof(lstFilesShare); i++) {
    Serial.print("File: ");
    Serial.print(lstFilesShare[i]);
    
    //add to routes
    server.on(lstFilesShare[i], []() {
      File_Download(lstFilesShare[i]);
    });
  }
*/
  
/*
  Serial.println("add /files/* to rotes");
  Dir dir = SPIFFS.openDir("");
  while (dir.next()) {
      Serial.print("File: ");
      const String fName = dir.fileName();
      Serial.print(fName);
      
      //add to routes
      server.on(fName, [](String fName) {
        File_Download(fName);
      });
  }  
*/

  //server.on("/other", []() {   //Define the handling function for the path
  //  server.send(200, "text / plain", "Other URL");
  //});
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
  server.on("/manifest.json", []() {
    File_Download("/manifest.json");
  });
  server.on("/", handleRootPath);    //Associate the handler function to the path


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
 
void handleRootPath() {            //Handler for the rooth path
  //server.send(200, "text/plain", "Hello world");
  server.send(200, "text/html; charset=utf-8", printPageIndex());
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
//String PROGMEM rv;
//char* PROGMEM buffrv;

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

    //to load file in browser
    //server.sendHeader("Content-Type", "text/text");
    server.sendHeader("Content-Disposition", "inline");
    //server.sendHeader("Connection", "close");
    server.streamFile(download, contentType);

/*
    //String PROGMEM rv;
    int n = download.size();
    buffrv = (char *) malloc(n);
    download.readBytes(buffrv,n);
    rv=buffrv;
    free(buffrv);

    //int n = download.size();
    //download.readBytes(rv,n);
    
    server.send(200, contentType, rv);

    
    //server.send(200, contentType, download.readString());
    //server.send(200, contentType, download.readString());
    
*/
    
    download.close();
  } else ReportFileNotPresent("download"); 
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
