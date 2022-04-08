#include <Servo.h>

const int servoOutputPin = 0;
const int servoMin = 450;
const int servoMax = 2600;
const int servoSensorPin = A0;

const int servoSensorValueThreshold = 165;

const int maxClosedPosition = 0;
const int maxOpenedPosition = 180;
const int positionOffset = 7;

int openedPosition;
int closedPosition;
int currentPosition;

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(INPUT, servoSensorPin);
  pinMode(OUTPUT, servoSensorPin);

  closedPosition = close(90, 45) + positionOffset;
  openedPosition = open(currentPosition, 90) - positionOffset;
}

void loop() {
}

int close(int startPosition, int minDegreesTraveled) {
  return turnServoUntilEndStop(startPosition, maxClosedPosition, startPosition, -1, maxClosedPosition, minDegreesTraveled);
}

int open(int startPosition, int minDegreesTraveled) {
  return turnServoUntilEndStop(startPosition, startPosition, maxOpenedPosition, 1, maxOpenedPosition, minDegreesTraveled);
}

int turnServoUntilEndStop(int startPosition, int leftNumber, int rightNumber, int incrementBy, int maxPosition, int minDegreesTraveled) {
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = startPosition; leftNumber < rightNumber; position += incrementBy) {
    int degreesTraveled = (position - startPosition) * incrementBy;
    if (hasHitEndstopAndTurnOneDegree(position, degreesTraveled, minDegreesTraveled)) {
      return position;
    }  
  }

  return maxPosition;
}

bool hasHitEndstopAndTurnOneDegree(int position, int degreesTraveled, int minDegreesTraveled) {
  bool hasTraveledFarEnough = degreesTraveled >= minDegreesTraveled;
  int servoSensorValue = analogRead(servoSensorPin);
  bool hasHitVoltageThreshold = servoSensorValue >= servoSensorValueThreshold;

  if (hasTraveledFarEnough && hasHitVoltageThreshold) {
    servo.detach();
    return true;
  } else {
    servo.write(position);
    currentPosition = position;
  }

  delay(30); 
  return false;
}
