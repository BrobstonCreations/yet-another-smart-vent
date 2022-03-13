#include <Servo.h>

int servoOutputPin = 0;
int servoMin = 450;
int servoMax = 2600;
int servoSensorPin = A0;

int upperLimit = 100;
int threshold = 165;

int globalStartPosition = 90;
int minDegreesTraveled = 40;

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(INPUT, servoSensorPin);
  pinMode(OUTPUT, servoSensorPin);
}

void loop() {
  open();
  close();
}

void open() {
  servo.attach(servoOutputPin, servoMin, servoMax);

  int startPosition = globalStartPosition;
  for(int position = startPosition; position < 180; position++) {
    int degreesTraveled = position - startPosition;
    if (turnOneDegreeUnlessAtEndStop(position, degreesTraveled)) {
      break;
    }  
  }
}

void close() {
  servo.attach(servoOutputPin, servoMin, servoMax);

  int startPosition = globalStartPosition;
  for(int position = startPosition; position > 40; position--) {
    int degreesTraveled = startPosition - position;
    if (turnOneDegreeUnlessAtEndStop(position, degreesTraveled)) {
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
