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
        Serial.println("Lower:" + loadedData.lowerLimit);
        Serial.println("Upper:" + loadedData.upperLimit);
        Serial.println("Current:" + loadedData.currentPosition);
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



void sendState() {
   char percentageString[3];
   int percentPosition = getPositionAsPercentage();
   itoa(percentPosition, percentageString, 10);
   client.publish(mqttStateTopic, percentageString, true);
}

float getTemperature() {
  float temp;
  do {
    DS18B20.requestTemperatures(); 
    temp = DS18B20.getTempCByIndex(0);
    delay(100);
  } while (temp == 85.0 || temp == (-127.0));
  return temp;
}


void sendTemp() {
   float temperature = getTemperature();
   dtostrf(temperature, 2, 2, temperatureString);
   client.publish(mqttTempTopic, temperatureString, true);
   Serial.println(temperatureString);
}
