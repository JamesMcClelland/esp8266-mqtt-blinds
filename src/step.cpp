#include <Arduino.h>
#include <ESPRotary.h>
#include <flash.h>
#include <sstream>
#include <string>

#define ROTARY_PIN1  D3     // IN1 on the ULN2003 driver 1	
#define ROTARY_PIN2  D4     // IN2 on the ULN2003 driver 1	
#define MOTOR_LEFT   D5     // IN3 on the ULN2003 driver 1	
#define MOTOR_RIGHT  D6     // IN4 on the ULN2003 driver 1	

int stepsPerRotation = 10000;
long currentPosition;
int speed;

ESPRotary rotary = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, 2);

void rotate(ESPRotary& r) {
   Serial.println(r.getPosition());
}

void showDirection(ESPRotary& r) {
  Serial.println(r.directionToString(r.getDirection()));
}

void setupMotor() {
    rotary.setChangedHandler(rotate);
    rotary.setLeftRotationHandler(showDirection);
    rotary.setRightRotationHandler(showDirection);

    currentPosition = getPositionInfo("currentPosition");
    speed = getSpeed();
}

void stepTo(long newLocation){
    // stepper.moveTo(newLocation);
    // stepper.setSpeed(1000);
    // while (stepper.distanceToGo() != 0)
    // {
        // stepper.runSpeedToPosition();
        // yield();
    // }

    saveSetting("currentPosition", String(newLocation));

    //MQTT SEND DATA
    // sendState();

    //Turn off motor spin
    digitalWrite(MOTOR_LEFT,LOW);
    digitalWrite(MOTOR_RIGHT,LOW);
}

void stepByTurnAmount(float amount) {
    long newPosition = getPositionInfo("currentPosition")+(amount*stepsPerRotation);

    stepTo(newPosition);
}

void stepByNumber(long number) {
    long newPosition = getPositionInfo("currentPosition")+number;
    stepTo(newPosition);
}

void stepToPercentage(int percentage) {
    //Gives us a value to multiply by
    float fractionPercent = (float)percentage / (float)100;
    long percentPosition = 0;

    long higher = getPositionInfo("upperLimit");
    long lower = getPositionInfo("lowerLimit");

    percentPosition = lower + (fractionPercent * (higher - lower));    
    stepTo(percentPosition);
}

int getPositionAsPercentage() {
    int positionP = 0;

    positionP = (int)abs(round( 
            (
                (float)(getPositionInfo("lowerLimit")-getPositionInfo("currentPosition")) / 
                (float)(getPositionInfo("upperLimit") - getPositionInfo("lowerLimit")) 
            ) * 100
            ));
    
    Serial.println("Current position as percentage:");
    Serial.println(positionP);
    return positionP;
}
