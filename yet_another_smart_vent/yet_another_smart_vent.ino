#include <FS.h>
#include <Servo.h>
#include "wifi.h"

#include <WEMOS_Motor.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <DoubleResetDetector.h>

Servo servo;
const int servoPin = 0;
const int servoPotentiometerPin = A0;
const int servoMin = 500;
const int servoMax = 3750;

const int maxOpenedPosition = 0;
const int maxClosedPosition = 120;
const int mediumPosition = maxClosedPosition / 2;

const int positionErrorTolerance = 2;

int openedPosition;
int closedPosition;
int openedPotentionmeterPosition;
int closedPotentionmeterPosition;

const int positionsLength = 5;
struct POSITION {
  int targetPosition;
  int potentiometerPosition;
};
POSITION positions[positionsLength];

uint8_t mqttRetryCounter = 0;

WiFiManager wifiManager;
WiFiClient wifiClient;
PubSubClient mqttClient;

WiFiManagerParameter custom_mqtt_server("mqtt server", "mqtt server", mqtt_server, sizeof(mqtt_server));
WiFiManagerParameter custom_mqtt_port("mqtt port", "mqtt port", mqtt_port, sizeof(mqtt_port));
WiFiManagerParameter custom_mqtt_username("mqtt username", "mqtt username", mqtt_username, sizeof(mqtt_username));
WiFiManagerParameter custom_mqtt_password("mqtt password", "mqtt password", mqtt_password, sizeof(mqtt_password));
WiFiManagerParameter custom_mqtt_topic("mqtt topic", "mqtt_topic", mqtt_topic, sizeof(mqtt_topic));

unsigned long lastMqttConnectionAttempt = millis();
const long mqttConnectionInterval = 60000;

char identifier[24];
#define AVAILABILITY_ONLINE "online"
#define AVAILABILITY_OFFLINE "offline"
char MQTT_COMMAND_TOPIC[128];
char MQTT_STATE_TOPIC[128];
char MQTT_AVAILABILITY_TOPIC[128];

#define DRD_TIMEOUT 1
#define DRD_ADDRESS 0
DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);

bool shouldSaveConfig = false;

void setup() {
  Serial.begin(9600);

  if (!drd.detectDoubleReset()) {
    pinMode(servoPin, OUTPUT);
    pinMode(servoPotentiometerPin, INPUT);
  
    snprintf(identifier, sizeof(identifier), "VENT-%X", ESP.getChipId());
  
    WiFi.hostname(identifier);
  
    loadConfig();
  
    snprintf(MQTT_COMMAND_TOPIC, 127, "%s/%s", "cmd", mqtt_topic);
    snprintf(MQTT_STATE_TOPIC, 127, "%s/%s", "stat", mqtt_topic);
    snprintf(MQTT_AVAILABILITY_TOPIC, 127, "%s/%s/%s", "tele", mqtt_topic, "LWT");

    setupWifi();
    mqttClient.setServer(mqtt_server, std::strtol(mqtt_port, nullptr, 10));
    mqttClient.setKeepAlive(10);
    mqttClient.setBufferSize(2048);
    mqttClient.setCallback(mqttCallback);
  
    mqttReconnect();
  
    printMqttTopicValues();

    calibrateClose(mediumPosition);
    clearPositions();
    calibrateOpen(mediumPosition);
  } else {
    Serial.println("Double click of reset detected. Clearing config and formatting storage...");
    resetWifiSettingsAndReboot();
  }
}

void loop() {
  drd.loop();
  mqttClient.loop();

  if (!mqttClient.connected() && (mqttConnectionInterval <= (millis() - lastMqttConnectionAttempt)) )  {
    lastMqttConnectionAttempt = millis();
    mqttReconnect();
  }
}

void configModeCallback (WiFiManager *wifiManager) {
  Serial.print("Entering WiFi Access Point config mode. Use a device to connect to Access Point ");
  Serial.print(identifier);
  Serial.println(".");
  Serial.print("Navigate to ");
  Serial.print(WiFi.softAPIP());
  Serial.println(" if not redirected to enter configuration values.");
  drd.stop();
}

void saveConfigCallback () {
  shouldSaveConfig = true;
}

void setupWifi() {
  wifiManager.setDebugOutput(false);
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_username);
  wifiManager.addParameter(&custom_mqtt_password);
  wifiManager.addParameter(&custom_mqtt_topic);

  WiFi.hostname(identifier);
  wifiManager.autoConnect(identifier);
  mqttClient.setClient(wifiClient);

  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(mqtt_username, custom_mqtt_username.getValue());
  strcpy(mqtt_password, custom_mqtt_password.getValue());
  strcpy(mqtt_topic, custom_mqtt_topic.getValue());

  if (shouldSaveConfig) {
    saveConfig();
    ESP.restart();
  } else {
    loadConfig();
  }
}

void resetWifiSettingsAndReboot() {
  ESP.eraseConfig();
  SPIFFS.format();
  delay(3000);
  ESP.restart();
}

void mqttReconnect()
{
  for (int attempt = 0; attempt < 3; ++attempt) {
    if (mqttClient.connect(identifier, mqtt_username, mqtt_password, MQTT_AVAILABILITY_TOPIC, 1, true, AVAILABILITY_OFFLINE)) {
      mqttClient.publish(MQTT_AVAILABILITY_TOPIC, AVAILABILITY_ONLINE, true);

      mqttClient.subscribe(MQTT_COMMAND_TOPIC);
      break;
    } else {
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, MQTT_COMMAND_TOPIC) == 0) {
    char payloadText[length + 1];
    snprintf(payloadText, length + 1, "%s", payload);

    if (isOpen(payloadText) && !isOpened()) {
      open();
    } else if (isClose(payloadText) && !isClosed()) {
      close();
    }
  }
}

boolean isMqttConnected() {
  return mqttClient.connected();
}

void open() {
  mqttClient.publish(MQTT_STATE_TOPIC, "opening", true);
  servo.attach(servoPin, servoMin, servoMax);

  int currentPosition = getCurrentPosition();
  for(int position = currentPosition; position >= openedPosition; position--) {
    servo.write(position);
    delay(20);
  }

  servo.detach();

  if (isOpened()) {
    mqttClient.publish(MQTT_STATE_TOPIC, "opened", true);
  }
}

void close() {
  mqttClient.publish(MQTT_STATE_TOPIC, "closing", true);
  servo.attach(servoPin, servoMin, servoMax);

  int currentPosition = getCurrentPosition();
  for(int position = currentPosition; position <= closedPosition; position++) {
    servo.write(position);
    delay(20);
  }

  servo.detach();

  if (isClosed()) {
    mqttClient.publish(MQTT_STATE_TOPIC, "closed", true);
  }
}

void calibrateOpen(int startPosition) {
  mqttClient.publish(MQTT_STATE_TOPIC, "opening", true);
  servo.attach(servoPin, servoMin, servoMax);

  for(int position = startPosition; position >= maxOpenedPosition; position--) {
    delayServoWrite(position);
    const int servoPotentiometerPosition = readServoPotentionmeterPosition();
    updatePreviousPositions(position, servoPotentiometerPosition);
    if (hasHitEndStop()) {
      openedPosition = determineEndStopPosition();
      openedPotentionmeterPosition = servoPotentiometerPosition;
      break;
    }
  }

  servo.detach();

  if (isOpened()) {
    mqttClient.publish(MQTT_STATE_TOPIC, "opened", true);
  }
}

void calibrateClose(int startPosition) {
  mqttClient.publish(MQTT_STATE_TOPIC, "closing", true);
  servo.attach(servoPin, servoMin, servoMax);

  for(int position = startPosition; position <= maxClosedPosition; position++) {
    delayServoWrite(position);
    const int servoPotentiometerPosition = readServoPotentionmeterPosition();
    updatePreviousPositions(position, servoPotentiometerPosition);
    if (hasHitEndStop()) {
      closedPosition = determineEndStopPosition();
      closedPotentionmeterPosition = servoPotentiometerPosition;
      break;
    }
  }

  servo.detach();
  
  if (isClosed()) {
    mqttClient.publish(MQTT_STATE_TOPIC, "closed", true);
  }
}

boolean isOpen(char* payloadText) {
  return strcmp(payloadText, "open") == 0;
}

boolean isClose(char* payloadText) {
  return strcmp(payloadText, "close") == 0;
}

boolean isOpened() {
  const int currentPosition = getCurrentPosition();
  const int upperTolerance = openedPosition + positionErrorTolerance;
  const int lowerTolerance = openedPosition - positionErrorTolerance;
  return currentPosition >= lowerTolerance && currentPosition <= upperTolerance;
}

boolean isClosed() {
  const int currentPosition = getCurrentPosition();
  const int upperTolerance = closedPosition + positionErrorTolerance;
  const int lowerTolerance = closedPosition - positionErrorTolerance;
  return currentPosition >= lowerTolerance && currentPosition <= upperTolerance;
}

int getCurrentPosition() {
  const int servoPotentiometerPosition = readServoPotentionmeterPosition();
  return map(servoPotentiometerPosition, openedPotentionmeterPosition, closedPotentionmeterPosition, openedPosition, closedPosition);
}

boolean hasHitEndStop() {
  const int currentPotentiometerPosition = positions[0].potentiometerPosition;
  for (int index = positionsLength - 1; index >= 1; index--) {
    if (currentPotentiometerPosition == positions[index].potentiometerPosition) {
      return true;
    }
  }
  return false;
}

int determineEndStopPosition() {
  const int currentPotentiometerPosition = positions[0].potentiometerPosition;
  for (int index = positionsLength - 1; index >= 1; index--) {
    if (currentPotentiometerPosition == positions[index].potentiometerPosition) {
      return positions[index].targetPosition;
    }
  }
  return positions[0].targetPosition;
}

void clearPositions() {
  for (int index = 0; index < positionsLength; index++) {
    positions[index].targetPosition = NULL;
    positions[index].potentiometerPosition = NULL;
  }
}

void updatePreviousPositions(int targetPosition, int potentiometerPosition) {
  for (int index = positionsLength - 1; index >= 1; index--) {
    const int nextIndex = index - 1;
    positions[index].targetPosition = positions[nextIndex].targetPosition;
    positions[index].potentiometerPosition = positions[nextIndex].potentiometerPosition;
  }
  positions[0].targetPosition = targetPosition;
  positions[0].potentiometerPosition = potentiometerPosition;
}

void delayServoWrite(int targetPosition) {
  servo.write(targetPosition);
  delayUntilStoppedMoving();
}

void delayUntilStoppedMoving() {
  while(!hasStoppedMoving());
}

boolean hasStoppedMoving() {
  const int servoPotentiometerPosition1 = readServoPotentionmeterPosition();
  const int servoPotentiometerPosition2 = readServoPotentionmeterPosition();
  const int servoPotentiometerPosition3 = readServoPotentionmeterPosition();
  if (servoPotentiometerPosition1 == servoPotentiometerPosition2 || servoPotentiometerPosition1 == servoPotentiometerPosition3 || servoPotentiometerPosition2 == servoPotentiometerPosition3) {
    return true;
  } else {
    return false;
  }
}

int readServoPotentionmeterPosition() {
  delay(10);
  return analogRead(servoPotentiometerPin);
}

void printMqttTopicValues() {
  Serial.print("MQTT_COMMAND_TOPIC: ");
  Serial.println(MQTT_COMMAND_TOPIC);
  Serial.print("MQTT_STATE_TOPIC: ");
  Serial.println(MQTT_STATE_TOPIC);
  Serial.print("MQTT_AVAILABILITY_TOPIC: ");
  Serial.println(MQTT_AVAILABILITY_TOPIC);
}
