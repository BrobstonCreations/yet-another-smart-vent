#include <Servo.h>

int servoOutputPin = 0;
int servoSensorPin = A0;
int threshold = 165;
int upperLimit = 100;
int servoMin = 450;
int servoMax = 2600;

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(servoOutputPin, servoMin, servoMax);
  pinMode(INPUT, servoSensorPin);
}

void loop() {

}
