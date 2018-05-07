void EEPROMBlank() {
    SavedObject cleanData = {
            1, /*initialised*/
            0, /*speed*/
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


