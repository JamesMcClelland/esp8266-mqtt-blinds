#include <Arduino.h>
#include <OneWire.h>	
#include <DallasTemperature.h>

#include <flash.h>
#include <step.h>
#include <user_interface.h>
#include <mqtt.h>

void setup() {	

    ESP.wdtDisable();	
    ESP.wdtEnable(WDTO_8S);	
    
    connectToHostWifi();

    setupEEPROM();
    setupMotor();
    setupRoutes();
    setupWifi();
    Serial.println("Why hello there neighbour");
}

void loop() {	
    //Todo: add in MQTT topic publish and subsribe;	
    // checkMQTT();
    //Check if below is needed 
    // client.setCallback(callback);	

    // turnAmount(1000);
    // delay(1000);
    // turnAmount(-1000);
    // delay(1000);

    handleHTTP();
}
