#include <Servo.h>

int servoOutputPin = 0;
int servoMin = 450;
int servoMax = 2600;
int servoSensorPin = A0;

int upperLimit = 100;
int threshold = 165;

Servo servo;

int startPosition = 90;

void setup() {
  Serial.begin(9600);
  pinMode(INPUT, servoSensorPin);
}

void loop() {
  Serial.print("startPosition:");
  Serial.println(startPosition);
  close(startPosition);
  open(startPosition);
}

void close(int bar) {
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = bar; position > 40; position--) {
    Serial.print("position:");
    Serial.print(position);
    int servoSensorValue = analogRead(servoSensorPin);
    Serial.print(" | ");
    Serial.print("servoSensorValue:");
    Serial.println(servoSensorValue);
  
    if (servoSensorValue >= threshold) {
      servo.detach();
      startPosition = position;
      break;
    } else {
      servo.write(position);
    }
 
    delay(100); 
  }
}

void open(int bar) {
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = bar; position < 180; position++) {
    Serial.print("position:");
    Serial.print(position);
    int servoSensorValue = analogRead(servoSensorPin);
    Serial.print(" | ");
    Serial.print("servoSensorValue:");
    Serial.println(servoSensorValue);
  
    if (servoSensorValue >= threshold) {
      servo.detach();
      startPosition = position;
      break;
    } else {
      servo.write(position);
    }
  
    delay(100); 
  }
}

