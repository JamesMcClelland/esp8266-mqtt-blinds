#include <Arduino.h>
#include <flash.h>
#include <EEPROM.h>	

int dataAddress = 0;

SavedObject loadedData;

void EEPROMBlank() {
    SavedObject cleanData = {
            1, /*initialised*/
            255, /*speed*/
            0,/*currentPosition*/
            0,/*lowerLimit*/
            0,/*upperLimit*/
    };
    EEPROM.put(dataAddress, cleanData);
    loadedData = cleanData;
    EEPROM.commit();
}

SavedObject setupEEPROM() {
    EEPROM.begin(1024);

    EEPROM.get( dataAddress, loadedData );
    if (loadedData.initialised != 1) {
        //Fill the EEPROM with empty data so we have a clean slate for reading.
        EEPROMBlank();
    }
    Serial.println( loadedData.initialised );
    Serial.println( loadedData.speed );
    Serial.println( loadedData.currentPosition );
    Serial.println( loadedData.lowerLimit );
    Serial.println( loadedData.upperLimit );

    return loadedData;

}

void saveSetting(String setting, String stringValue) {
    /*Todo: there must be a way of getting a property of a struct by its key e.g loadedData[setting]*/
    if (setting == "initialised") {
        loadedData.initialised = stringValue.toInt();
    } else if(setting == "upperLimit") {
        loadedData.upperLimit = stringValue.toInt();
    } else if(setting == "lowerLimit") {
        loadedData.lowerLimit = stringValue.toInt();
    }else if(setting ==  "speed") {
        loadedData.speed = stringValue.toInt();
    } else if(setting ==  "currentPosition") {
        loadedData.currentPosition = stringValue.toInt();
    }
    EEPROM.put(dataAddress, loadedData);
    EEPROM.commit();
}

long getPositionInfo(String type) {
    if(type == "upperLimit") {
        return loadedData.upperLimit;
    } else if(type == "lowerLimit") {
        return loadedData.lowerLimit;
    } else if(type ==  "currentPosition") {
        return loadedData.currentPosition;
    }
}

int getSpeed() {
    return loadedData.speed;
}