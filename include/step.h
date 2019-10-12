#include <ESPRotary.h>

void rotate(ESPRotary& r);

void showDirection(ESPRotary& r);

void setupMotor();

void stepTo(long newLocation);

void stepByTurnAmount(float amount);

void stepByNumber(long number);

void stepToPercentage(int percentage);

int getPositionAsPercentage();
