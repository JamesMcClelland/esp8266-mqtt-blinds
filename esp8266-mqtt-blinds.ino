//#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "FS.h"

#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <AccelStepper.h>

//#include "1_flash.ino"
//#include "2_routes.ino"
//#include "3_step.ino"

/* Set these to your desired credentials. */
const char *ssid = "ESP-8266-Blinds";
const char *password = "OpenSesame";

ESP8266WebServer server(80);

#define HALFSTEP 8

#define motorPin1  D3     // IN1 on the ULN2003 driver 1
#define motorPin2  D4     // IN2 on the ULN2003 driver 1
#define motorPin3  D5     // IN3 on the ULN2003 driver 1
#define motorPin4  D6     // IN4 on the ULN2003 driver 1

AccelStepper stepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

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


    //Todo: add in connecting to existing wifi point if present in EEPROM.

    SPIFFS.begin();

}

void loop() {
    //Todo: add in MQTT topic publish and subsribe;
    server.handleClient();

//Serial.println("1");
//    stepByTurnAmount(1);
//    delay(2000);
//    Serial.println("2");
//    stepByTurnAmount(-1);
//    delay(2000);
//    Serial.println("3");
//    stepByTurnAmount(1);
//    delay(2000);
//    Serial.println("4");
//    stepByTurnAmount(-1);
//    delay(2000);
}
