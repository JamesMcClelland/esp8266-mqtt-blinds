#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>	

void connectToHostWifi();

void setupWifi();

void reconnect();

void callback(char* topic, byte* payload, unsigned int length);

void sendState();

float getTemperature();

void sendTemp();

void checkMQTT();
