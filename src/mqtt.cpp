#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>	
#include <step.h>
#include <config.h>


WiFiClient espClient;
PubSubClient client(espClient);	

void sendState() {
   char percentageString[3];
   int percentPosition = getPositionAsPercentage();
   itoa(percentPosition, percentageString, 10);
   client.publish(mqttStateTopic, percentageString, true);
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    Serial.println("CB1");

    char message[length + 1];
    for (int i = 0; i < length; i++) {
        message[i] = (char)payload[i];
    }
    Serial.println("CB2");
    Serial.println(atoi(message));
    stepToPercentage(atoi(message));
    Serial.println("CB3");
    sendState();
}

void connectToHostWifi() {
    Serial.begin(115200);	
    Serial.println();	
    Serial.print("Configuring access point...");	
    /* You can remove the password parameter if you want the AP to be open. */	
    WiFi.softAP(ssid, password);	

    IPAddress myIP = WiFi.softAPIP();	
    Serial.print("AP IP address: ");	
    Serial.println(myIP);	
}

void setupWifi() {
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(yourSsid);

        WiFi.begin(yourSsid, yourPassword);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }

        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        client.setServer(mqttServer, mqttPort);
        client.setCallback(callback);
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(mqttClientID, mqttUsername, mqttPassword)) {
            Serial.println("connected");
            client.subscribe(mqttSetopic);
            sendState();
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void checkMQTT() {
    if (!client.connected()) {	
        reconnect();	
    }	
    client.loop();	
}
