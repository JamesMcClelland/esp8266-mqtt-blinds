int dataAddress = 0;

struct SavedObject {
    int initialised;
    char ssid[32];
    char pass[64];
    int speed;
    int stepsInRange;
    int currentPosition;
    int lowerLimit;
    int upperLimit;
    char clientId[64];
    char server[64];
    char username[64];
    char password[64];
};

SavedObject loadedData; //Variable to store custom object read from EEPROM.


void EEPROMBlank() {
    SavedObject cleanData = {
            1, /*initialised*/
            "", /*ssid*/
            "", /*pass*/
            0, /*speed*/
            0, /*stepsInRange*/
            0,/*currentPosition*/
            0,/*lowerLimit*/
            0,/*upperLimit*/
            "", /*clientId*/
            "", /*server*/
            "", /*username*/
            "", /*password*/
    };
    EEPROM.put(dataAddress, cleanData);
    loadedData = cleanData;
    EEPROM.commit();
}

void setupEEPROM() {
    EEPROM.begin(1024);

    EEPROM.get( dataAddress, loadedData );
    if (loadedData.initialised != 1) {
        //Fill the EEPROM with empty data so we have a clean slate for reading.
        EEPROMBlank();
    }
    Serial.println( loadedData.initialised );
    Serial.println( loadedData.ssid );
    Serial.println( loadedData.pass );
    Serial.println( loadedData.speed );
    Serial.println( loadedData.stepsInRange );
    Serial.println( loadedData.currentPosition );
    Serial.println( loadedData.lowerLimit );
    Serial.println( loadedData.upperLimit );
    Serial.println( loadedData.clientId );
    Serial.println( loadedData.server );
    Serial.println( loadedData.username );
    Serial.println( loadedData.password );
    
}

void saveSetting(String setting, int value, String stringValue) {
    /*Todo: there must be a way of getting a property of a struct by its key e.g loadedData[setting]*/
    if (setting == "initialised") {
        loadedData.initialised = value;
    } else if(setting == "upperLimit") {
        loadedData.upperLimit = value;
    } else if(setting == "ssid") {
      stringValue.toCharArray(loadedData.ssid, 32);
    } else if(setting ==  "pass") {
      stringValue.toCharArray(loadedData.pass, 64);
    } else if(setting ==  "speed") {
        loadedData.speed = value;
    } else if(setting ==  "stepsInRange") {
        loadedData.stepsInRange = value;
    } else if(setting ==  "currentPosition") {
        loadedData.currentPosition = value;
    } else if(setting == "lowerLimit") {
        loadedData.lowerLimit = value;
    } else if(setting ==  "clientId") {
        stringValue.toCharArray(loadedData.clientId, 64);
    } else if(setting ==  "server") {
       stringValue.toCharArray(loadedData.server, 64);
    } else if(setting ==  "username") {
        stringValue.toCharArray(loadedData.username, 64);
    } else if(setting ==  "password") {
      stringValue.toCharArray(loadedData.password, 64);
    }
    EEPROM.put(dataAddress, loadedData);
    EEPROM.commit();
}


