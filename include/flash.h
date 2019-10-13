#include <Arduino.h>
struct SavedObject {	
    int initialised;	
    int speed;
    long startPosition;	
    long lowerLimit;
    long upperLimit;
};	

SavedObject setupEEPROM();

void saveSetting(String setting, String stringValue);

long getPositionInfo(String type);

int getSpeed();