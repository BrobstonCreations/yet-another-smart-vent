#include <Servo.h>

const int servoOutputPin = 0;
const int servoMin = 450;
const int servoMax = 2600;
const int servoSensorPin = A0;

const int servoSensorValueThreshold = 165;

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
  servo.attach(servoOutputPin, servoMin, servoMax);
  int minPosition = 0;

  for(int position = startPosition; position > minPosition; position--) {
    int degreesTraveled = startPosition - position;
    if (turnOneDegreeUnlessAtEndStop(position, degreesTraveled, minDegreesTraveled)) {
      return position;
    }  
  }

  return minPosition;
}

int open(int startPosition, int minDegreesTraveled) {
  servo.attach(servoOutputPin, servoMin, servoMax);
  int maxPosition = 180;

  for(int position = startPosition; position < maxPosition; position++) {
    int degreesTraveled = position - startPosition;
    if (turnOneDegreeUnlessAtEndStop(position, degreesTraveled, minDegreesTraveled)) {
      return position;
    }  
  }

  return maxPosition;
}

bool turnOneDegreeUnlessAtEndStop(int position, int degreesTraveled, int minDegreesTraveled) {
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
