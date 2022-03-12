#include <Servo.h>

int servoOutputPin = 0;
int servoMin = 450;
int servoMax = 2600;
int servoSensorPin = A0;

int upperLimit = 100;
int threshold = 165;

Servo servo;

bool hasHitEndStop = false;

void setup() {
  Serial.begin(9600);
  servo.attach(servoOutputPin, servoMin, servoMax);
  pinMode(INPUT, servoSensorPin);
  servo.write(90);
}

void loop() {
  for(int i = 90; i < 180; i++) {
    int servoSensorValue = analogRead(servoSensorPin);
    Serial.print("servoSensorValue:");
    Serial.println(servoSensorValue);
    Serial.print("hasHitEndStop:");
    Serial.println(hasHitEndStop);

    if (!hasHitEndStop) {
      if (servoSensorValue >= threshold) {
        hasHitEndStop = true;
      } else {
        servo.write(i);
      }
    }
    
    delay(250);
  }
}
