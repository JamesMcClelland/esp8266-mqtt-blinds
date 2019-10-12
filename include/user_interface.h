#include <Arduino.h>
#include <ESP8266WebServer.h>

bool handleFileRead(String path);

String getContentType(String filename);

void speedChange();

void limitSet();

void manualTurn();

void goTo();

void softReset();

void setupRoutes();

void handleHTTP();