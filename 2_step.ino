/*
 * https://grahamwideman.wikispaces.com/Motors-+28BYJ-48+Stepper+motor+notes
 */
int stepsPerRotation = 4076;

void setupStepper() {
  stepper.moveTo(1000);
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

void stepToZero() {
    stepTo(loadedData.lowerLimit);
}

void stepToHundred() {
    stepTo(loadedData.upperLimit);
}