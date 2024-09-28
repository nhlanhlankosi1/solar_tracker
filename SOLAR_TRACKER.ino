#include <Servo.h>

const int baseServoPin = 10; 
const int topServoPin = 8; 
const int photoResistorPins[] = {A0, A1, A2, A3}; // A0 - top, A3 - bottom, left - A1, right - A2;
const int smoothingFactor = 8;

Servo baseServo;
Servo topServo;

int baseServoPosition = 90; 
int topServoPosition = 90; 

void setup() {
  baseServo.attach(baseServoPin);
  topServo.attach(topServoPin);
  baseServo.write(baseServoPosition);
  topServo.write(topServoPosition);
}

int getMaxPhotoResistorValue(int a, int b) {
  return (a > b) ? a : b;
}

void loop() {
  int photoResistorValues[] = {analogRead(photoResistorPins[0]), 
                               analogRead(photoResistorPins[1]), 
                               analogRead(photoResistorPins[2]), 
                               analogRead(photoResistorPins[3])};

  int maxPhotoResistorValue = getMaxPhotoResistorValue(getMaxPhotoResistorValue(photoResistorValues[0], 
                                     getMaxPhotoResistorValue(photoResistorValues[1], 
                                         getMaxPhotoResistorValue(photoResistorValues[2], 
                                             photoResistorValues[3]))), 
                                     getMaxPhotoResistorValue(photoResistorValues[1], 
                                         getMaxPhotoResistorValue(photoResistorValues[2], 
                                             photoResistorValues[3])));

  int newBaseServoPosition;
  int newTopServoPosition;

  if (photoResistorValues[1] > photoResistorValues[2]) {
    newBaseServoPosition = map(photoResistorValues[1], 0, 1023, 0, 180);
  } else {
    newBaseServoPosition = map(photoResistorValues[2], 0, 1023, 0, 180);
  }

  if (photoResistorValues[3] > photoResistorValues[0]) {
    newTopServoPosition = map(photoResistorValues[3], 0, 1023, 0, 180);
  } else {
    newTopServoPosition = map(photoResistorValues[0], 0, 1023, 0, 180);
  }

  // Smoothing
  baseServoPosition = (baseServoPosition * (smoothingFactor - 1) + newBaseServoPosition) / smoothingFactor;
  topServoPosition = (topServoPosition * (smoothingFactor - 1) + newTopServoPosition) / smoothingFactor;

  baseServo.write(baseServoPosition);
  topServo.write(topServoPosition);

  delay(100);
}