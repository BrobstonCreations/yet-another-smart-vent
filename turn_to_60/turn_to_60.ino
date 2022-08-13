#include <Servo.h>

Servo servo;
const int servoPin = 0;
const int servoPotentiometerPin = A0;
const int servoMin = 500;
const int servoMax = 3750;

void setup() {
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
  pinMode(servoPotentiometerPin, INPUT);
  servo.attach(servoPin, servoMin, servoMax);
}

void loop() {
  servo.write(60);
}
