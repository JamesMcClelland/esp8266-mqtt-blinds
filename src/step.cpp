#include <Arduino.h>
#include <ESPRotary.h>
#include <flash.h>
#include <sstream>
#include <string>

#define ROTARY_PIN1  D1     // IN1 on the ULN2003 driver 1	
#define ROTARY_PIN2  D2     // IN2 on the ULN2003 driver 1	
#define MOTOR_LEFT   D3     // IN3 on the ULN2003 driver 1	
#define MOTOR_RIGHT  D4     // IN4 on the ULN2003 driver 1	

int stepsPerRotation = 4100;
long currentPosition;
long startPosition;
long currentRotaryPosition = 0;
int speed;

int upperLimit;
int lowerLimit;

ESPRotary rotary = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, 2);

void rotate(ESPRotary& r) {
   currentRotaryPosition = startPosition+r.getPosition();
//    Serial.println(r.getPosition());
}

void showDirection(ESPRotary& r) {

}

void setupMotor() {
    rotary.setChangedHandler(rotate);
    rotary.setLeftRotationHandler(showDirection);
    rotary.setRightRotationHandler(showDirection);

    startPosition = getPositionInfo("startPosition");
    Serial.println("Loaded start position");
    Serial.println(startPosition);
    currentRotaryPosition = startPosition;
    lowerLimit = getPositionInfo("lowerLimit");
    upperLimit = getPositionInfo("upperLimit");
    speed = getSpeed();

    pinMode(MOTOR_LEFT, OUTPUT);
    pinMode(MOTOR_RIGHT, OUTPUT);
}

void stepTo(int position) {
    
    Serial.println("");
    Serial.println("Current position");
    Serial.println(currentRotaryPosition);
    Serial.println("New position");
    Serial.println(position);
    
    if(currentRotaryPosition <= position) {
        Serial.println("Going left");
        while(currentRotaryPosition <= position) {
            rotary.loop();
            yield();
            digitalWrite(MOTOR_LEFT, LOW);
            digitalWrite(MOTOR_RIGHT, HIGH);
        }
    } else {
        Serial.println("Going right");
        while(currentRotaryPosition >= position) {
            rotary.loop();
            yield();
            digitalWrite(MOTOR_LEFT, HIGH);
            digitalWrite(MOTOR_RIGHT, LOW);
        }
    }
    digitalWrite(MOTOR_LEFT, LOW);
    digitalWrite(MOTOR_RIGHT, LOW);
    saveSetting("startPosition", String(currentRotaryPosition));
    Serial.println("New Position");
    Serial.println(currentRotaryPosition);
}

void stepByTurnAmount(float amount) {
    long newPosition = currentRotaryPosition+(amount*stepsPerRotation);
    stepTo(newPosition);
}

void stepByNumber(long number) {
    long newPosition = currentRotaryPosition+number;
    stepTo(newPosition);
}

void stepToPercentage(int percentage) {
    //Gives us a value to multiply by
    float fractionPercent = (float)percentage / (float)100;
    long percentPosition = 0;

    percentPosition = lowerLimit + (fractionPercent * (upperLimit - lowerLimit));    
    stepTo(percentPosition);
}

//Todo: fix this function to properly return the current state
int getPositionAsPercentage() {
    int positionP = 0;

    positionP = (int)abs( round( ( (float)(lowerLimit-currentPosition) / (float)(upperLimit - lowerLimit) ) * 100) );
    
    Serial.println("Current position as percentage:");
    Serial.println(positionP);
    return positionP;
}
