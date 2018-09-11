/*
 * https://grahamwideman.wikispaces.com/Motors-+28BYJ-48+Stepper+motor+notes
 */
int stepsPerRotation = 4076;

void setupStepper() {
    stepper.setCurrentPosition(loadedData.currentPosition);
    stepper.setMaxSpeed(1000);
    stepper.setSpeed(1000);
//    stepper.setAcceleration(500);
}

void stepTo(long newLocation){
    stepper.moveTo(newLocation);
    stepper.setSpeed(1000);
    while (stepper.distanceToGo() != 0)
    {
        stepper.runSpeedToPosition();
        yield();
    }
    saveSetting("currentPosition", String(newLocation));
    loadedData.currentPosition = newLocation;
    sendState();

    digitalWrite(D3,LOW);
    digitalWrite(D4,LOW);
    digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
}

void stepByTurnAmount(float amount) {
    long newPosition = loadedData.currentPosition+(amount*stepsPerRotation);
    stepTo(newPosition);
}

void stepByNumber(long number) {
    long newPosition = loadedData.currentPosition+number;
    stepTo(newPosition);
}

void stepToPercentage(int percentage) {
    //Gives us a value to multiply by
    float fractionPercent = (float)percentage / (float)100;
    long percentPosition = 0;

    int higher = loadedData.upperLimit;
    int lower = loadedData.lowerLimit;

    percentPosition = lower + (fractionPercent * (higher - lower));
    

    Serial.println("ZZZ");
    Serial.println(higher);
    Serial.println(lower);
    Serial.println(fractionPercent);
    Serial.println(percentPosition);
    Serial.println(percentage);
    
    stepTo(percentPosition);
}

int getPositionAsPercentage() {
    int positionP = 0;

    positionP = (int)abs( round( ( (float)(loadedData.lowerLimit-loadedData.currentPosition) / (float)(loadedData.upperLimit - loadedData.lowerLimit) ) * 100) );
    
    Serial.println("Current position as percentage:");
    Serial.println(positionP);
    return positionP;
}
