#include <Arduino.h>
#include <FS.h>
#include <ESP8266WebServer.h>
#include <sstream>
#include <string>

#include <flash.h>
#include <step.h>

ESP8266WebServer server(80);	

/*
Massive Thanks to https://github.com/tttapa for the code for serving static files
https://tttapa.github.io/ESP8266/Chap11%20-%20SPIFFS.html
*/
bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";         // If a folder is requested, send the index file
  String contentType = getContentType(path);            // Get the MIME type
  if (SPIFFS.exists(path)) {                            // If the file exists
    File file = SPIFFS.open(path, "r");                 // Open it
    server.streamFile(file, contentType); // And send it to the client
    file.close();                                       // Then close the file again
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;                                         // If the file doesn't exist, return false
}


String getContentType(String filename) { // convert the file extension to the MIME type
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  return "text/plain";
}

void speedChange() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "amount") {
            int amount = server.arg(i).toInt();
            saveSetting("speed", String(amount));
            break;
        }
    }
    server.send(200, "text/html", "ok");
}

void limitSet() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "amount") {
            int amount = server.arg(i).toInt();
            String stringAmount = String(amount);            
            if (amount == 0) {
                saveSetting("lowerLimit", String(getPositionInfo("startPosition")));
            } else if(amount == 100) {
                saveSetting("upperLimit", String(getPositionInfo("startPosition")));
            }
            break;
        }
    }
    server.send(200, "text/html", "ok");
}

void manualTurn() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "amount") {
            float amount = server.arg(i).toFloat();
            stepByTurnAmount(amount);
            break;
        }
    }
    server.send(200, "text/html", "ok");
}

void goTo() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "place") {
            stepToPercentage(server.arg(i).toInt());
            break;
        }
    }
    server.send(200, "text/html", "ok");
}

void softReset() {
    server.send(200, "text/html", "ok");
    ESP.restart();
}

void setupRoutes(){
    SPIFFS.begin();
    server.begin();
    //Todo: add more routes
    server.on("/speed", speedChange);
    server.on("/limit", limitSet);
    server.on("/turn", manualTurn);
    server.on("/goto", goTo);
    server.on("/reset", softReset);

    server.onNotFound([]() {                              // If the client requests any URI
    if (!handleFileRead(server.uri()))                  // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
    });

}

void handleHTTP() {
    server.handleClient();
}
