#include <Servo.h>

Servo servo;
const int servoPin = 0;
const int servoMin = 500;
const int servoMax = 3750;

void setup() {
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin, servoMin, servoMax);
}

void loop() {
  servo.write(60);
}
