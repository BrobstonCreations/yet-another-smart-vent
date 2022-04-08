#include <Servo.h>

int servoOutputPin = 0;
int servoMin = 450;
int servoMax = 2600;
int servoSensorPin = A0;

int upperLimit = 100;
int threshold = 165;

int globalStartPosition = 90;
int minDegreesTraveled = 40;

int openedPosition;
int closedPosition;

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(INPUT, servoSensorPin);
  pinMode(OUTPUT, servoSensorPin);

  closedPosition = close(globalStartPosition);
  Serial.print("closedPosition: ");
  Serial.println(closedPosition);
  openedPosition = open(closedPosition);
  Serial.print("openedPosition: ");
  Serial.println(openedPosition);
}

void loop() {
}

int open(int startPosition) {
  servo.attach(servoOutputPin, servoMin, servoMax);
  int maxPosition = 180;

  for(int position = startPosition; position < maxPosition; position++) {
    int degreesTraveled = position - startPosition;
    if (turnOneDegreeUnlessAtEndStop(position, degreesTraveled)) {
      return position;
    }  
  }

  return maxPosition;
}

int close(int startPosition) {
  servo.attach(servoOutputPin, servoMin, servoMax);
  int minPosition = 0;

  for(int position = startPosition; position > minPosition; position--) {
    int degreesTraveled = startPosition - position;
    if (turnOneDegreeUnlessAtEndStop(position, degreesTraveled)) {
      return position;
    }  
  }

  return minPosition;
}

bool turnOneDegreeUnlessAtEndStop(int position, int degreesTraveled) {
  bool hasTraveledFarEnough = degreesTraveled >= minDegreesTraveled;
  int servoSensorValue = analogRead(servoSensorPin);
  bool hasHitVoltageThreshold = servoSensorValue >= threshold;

  if (hasTraveledFarEnough && hasHitVoltageThreshold) {
    servo.detach();
    return true;
  } else {
    servo.write(position);
  }

  delay(100); 
  return false;
}
