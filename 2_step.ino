/*
 * https://grahamwideman.wikispaces.com/Motors-+28BYJ-48+Stepper+motor+notes
 */
int stepsPerRotation = 4076;

void setupStepper() {
    stepper.setCurrentPosition(loadedData.currentPosition);
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
}

void stepTo(long newLocation){
    stepper.moveTo(newLocation);
    while (stepper.distanceToGo() != 0)
    {
        stepper.run();
        yield();
    }
    saveSetting("currentPosition", String(newLocation));
    loadedData.currentPosition = newLocation;
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

    if (loadedData.lowerLimit > loadedData.upperLimit) {
        percentPosition = fractionPercent * (loadedData.lowerLimit - loadedData.upperLimit);
    } else {
        percentPosition = fractionPercent * (loadedData.upperLimit - loadedData.lowerLimit);
    }

    Serial.println("Stepping to position:");
    Serial.println(percentPosition);
    Serial.println("Stepping to percentage:");
    Serial.println(percentage);
    
    stepTo(percentPosition);
}

void stepToZero() {
    stepTo(loadedData.lowerLimit);
}

void stepToHundred() {
    stepTo(loadedData.upperLimit);
}

int getPositionAsPercentage() {
    int positionP = 0;
    if (loadedData.lowerLimit > loadedData.upperLimit) {
        positionP = (int)abs( round( ( (float)(loadedData.upperLimit-loadedData.currentPosition) / (float)(loadedData.lowerLimit - loadedData.upperLimit) ) * 100) );
    } else {
        positionP = (int)abs( round( ( (float)(loadedData.lowerLimit-loadedData.currentPosition) / (float)(loadedData.upperLimit - loadedData.lowerLimit) ) * 100) );
    }
    Serial.println("Current position as percentage:");
    Serial.println(positionP);
    return positionP;
}
