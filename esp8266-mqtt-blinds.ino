//#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "FS.h"
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <AccelStepper.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "config.h"
/*
 * Config file contains:
//Host Wifi
const char *ssid = "ESP-8266-Blinds";
const char *password = "OpenSesame";

//Connect to wifi
const char *yourSsid = "";
const char *yourPassword = "";

//MQTT Details
const char *mqttServer = "";
const int   mqttPort = 1883;
const char *mqttUsername = "";
const char *mqttPassword = "";
const char *mqttClientID = "ESP8266-Blinds-0pKi4y8";
const char* mqttStateTopic = "home/office/blinds";
const char* mqttSetopic = "home/office/blinds/set";
const char* mqttTempTopic = "home/office/temperature";
 */

ESP8266WebServer server(80);

#define HALFSTEP 8

#define motorPin1  D3     // IN1 on the ULN2003 driver 1
#define motorPin2  D4     // IN2 on the ULN2003 driver 1
#define motorPin3  D5     // IN3 on the ULN2003 driver 1
#define motorPin4  D6     // IN4 on the ULN2003 driver 1

AccelStepper stepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

WiFiClient espClient;
PubSubClient client(espClient);

#define TEMP_SENSOR D2

OneWire oneWire(TEMP_SENSOR);
DallasTemperature DS18B20(&oneWire);

int dataAddress = 0;

char temperatureString[6];

struct SavedObject {
    int initialised;
    int speed;
    long currentPosition;
    long lowerLimit;
    long upperLimit;
};

SavedObject loadedData; //Variable to store custom object read from EEPROM.

long previousMillis = 0;
long interval = 60000;   

void setup() {

    ESP.wdtDisable();
    ESP.wdtEnable(WDTO_8S);
  
    Serial.begin(115200);
    Serial.println();
    Serial.print("Configuring access point...");
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    setupEEPROM();
    setupRoutes();
    setupStepper();
    setupWifi();
    SPIFFS.begin();    
    DS18B20.begin();

}

void loop() {
    //Todo: add in MQTT topic publish and subsribe;

    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    client.setCallback(callback);
    server.handleClient();

    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      sendTemp();
    }
    
}
