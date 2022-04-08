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

  close(globalStartPosition);
  Serial.print("closedPosition: ");
  Serial.println(closedPosition);
  open(closedPosition);
  Serial.print("openedPosition: ");
  Serial.println(openedPosition);
}

void loop() {
}

void open(int startPosition) {
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = startPosition; position < 180; position++) {
    int degreesTraveled = position - startPosition;
    if (turnOneDegreeUnlessAtEndStop(position, degreesTraveled)) {
      openedPosition = position;
      break;
    }  
  }
}

void close(int startPosition) {
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = startPosition; position > 0; position--) {
    int degreesTraveled = startPosition - position;
    if (turnOneDegreeUnlessAtEndStop(position, degreesTraveled)) {
      closedPosition = position;
      break;
    }  
  }
}

bool turnOneDegreeUnlessAtEndStop(int position, int degreesTraveled) {
  bool hasTraveledFarEnough = degreesTraveled >= minDegreesTraveled;
  int servoSensorValue = analogRead(servoSensorPin);
  bool hasHitVoltageThreshold = servoSensorValue >= threshold;

  if (hasTraveledFarEnough && hasHitVoltageThreshold) {
    servo.detach();
    globalStartPosition = position;
    return true;
  } else {
    servo.write(position);
  }

  delay(100); 
  return false;
}
