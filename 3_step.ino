/*
 * https://grahamwideman.wikispaces.com/Motors-+28BYJ-48+Stepper+motor+notes
 */
int stepsPerRotation = 2038;

void setupStepper() {
  stepper.setMaxSpeed(1000.0);
  stepper.move(1);  // I found this necessary
  stepper.setSpeed(1000);

  stepper.setMaxSpeed(1000.0); 
  stepper.move(-1);  // I found this necessary
  stepper.setSpeed(1000);
}

void stepTo(int newLocation){
  stepper.moveTo(newLocation);
  for(int i = 0; i< 100; i++) {
     stepper.runSpeed();
     delay(5);
  }
}

void stepByTurnAmount(int amount) {
    int newPosition = loadedData.currentPosition+(amount*stepsPerRotation);
    stepTo(newPosition);
}

void stepByNumber(int number) {
    int newPosition = loadedData.currentPosition+number;
    stepTo(newPosition);
}
