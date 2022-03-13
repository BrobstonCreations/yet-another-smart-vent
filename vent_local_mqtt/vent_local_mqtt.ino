#include <Servo.h>

int servoOutputPin = 0;
int servoMin = 450;
int servoMax = 2600;
int servoSensorPin = A0;

int upperLimit = 100;
int threshold = 165;

Servo servo;

int globalStartPosition = 90;

void setup() {
  Serial.begin(9600);
  pinMode(INPUT, servoSensorPin);
}

void loop() {
  Serial.print("globalStartPosition:");
  Serial.println(globalStartPosition);
  close(globalStartPosition);
  open(globalStartPosition);
}

void close(int startPosition) {
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = startPosition; position > 40; position--) {
    bool shouldBreak = turnOneDegreeUnlessAtEndStop(position);
    if (shouldBreak) {
      break;
    }  
  }
}

void open(int startPosition) {
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = startPosition; position < 180; position++) {
    bool shouldBreak = turnOneDegreeUnlessAtEndStop(position);
    if (shouldBreak) {
      break;
    }
  }
}

bool turnOneDegreeUnlessAtEndStop(int position) {
  Serial.print("position:");
  Serial.print(position);
  int servoSensorValue = analogRead(servoSensorPin);
  Serial.print(" | ");
  Serial.print("servoSensorValue:");
  Serial.println(servoSensorValue);

  if (servoSensorValue >= threshold) {
    servo.detach();
    globalStartPosition = position;
    return true;
  } else {
    servo.write(position);
  }

  delay(100); 
  return false;
}
