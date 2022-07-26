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

const int servoOutputPin = 0;
const int servoMin = 450;
const int servoMax = 2600;
const int servoSensorPin = A0;

const int servoSensorValueThreshold = 165;

const int maxClosedPosition = 0;
const int maxOpenedPosition = 180;

const int delayBetweenMoves = 40;

const int initialMoveOffset = 4;
const int endstopOffset = 5;
int openedPosition;
int closedPosition;
int currentPosition;

Servo servo;

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
    pinMode(servoSensorPin, INPUT);
    pinMode(servoOutputPin, OUTPUT);
  
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

    closedPosition = calibrateClose(90, 45);
    openedPosition = calibrateOpen(currentPosition, 90);
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
      if (isOpened()) {
        mqttClient.publish(MQTT_STATE_TOPIC, "opened", true);
      }
    } else if (isClose(payloadText) && !isClosed()) {
      close();
      if (isClosed()) {
        mqttClient.publish(MQTT_STATE_TOPIC, "closed", true);
      }
    }
  }
}

boolean isMqttConnected() {
  return mqttClient.connected();
}

void open() {
  mqttClient.publish(MQTT_STATE_TOPIC, "opening", true);
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = currentPosition + initialMoveOffset; position <= openedPosition; position++) {
    currentPosition = position;
    servo.write(position);
    delay(delayBetweenMoves);
  }
//  currentPosition = openedPosition;
//  servo.write(openedPosition);
//  delay(300);

  servo.detach();
}

void close() {
  mqttClient.publish(MQTT_STATE_TOPIC, "closing", true);
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = currentPosition - initialMoveOffset; position >= closedPosition; position--) {
    currentPosition = position;
    servo.write(position);
    delay(delayBetweenMoves);
  }
//  currentPosition = closedPosition;
//  servo.write(closedPosition);
//  delay(300);

  servo.detach();
}

int calibrateOpen(int startPosition, int minDegreesTraveled) {
  mqttClient.publish(MQTT_STATE_TOPIC, "opening", true);
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = startPosition; position <= maxOpenedPosition; position++) {
    int degreesTraveled = position - startPosition;
    if (hasHitEndstopAndTurnOneDegree(position, degreesTraveled, minDegreesTraveled)) {
      return position - endstopOffset;
    }  
  }

  mqttClient.publish(MQTT_STATE_TOPIC, "opened", true);

  return maxOpenedPosition;
}

int calibrateClose(int startPosition, int minDegreesTraveled) {
  mqttClient.publish(MQTT_STATE_TOPIC, "closing", true);
  servo.attach(servoOutputPin, servoMin, servoMax);

  for(int position = startPosition; position >= maxClosedPosition; position--) {
    int degreesTraveled = startPosition - position;
    if (hasHitEndstopAndTurnOneDegree(position, degreesTraveled, minDegreesTraveled)) {
      return position + endstopOffset;
    }
  }

  mqttClient.publish(MQTT_STATE_TOPIC, "closed", true);

  return maxClosedPosition;
}

bool hasHitEndstopAndTurnOneDegree(int position, int degreesTraveled, int minDegreesTraveled) {
  bool hasTraveledFarEnough = degreesTraveled >= minDegreesTraveled;
  int servoSensorValue = analogRead(servoSensorPin);
  bool hasHitVoltageThreshold = servoSensorValue >= servoSensorValueThreshold;

  currentPosition = position;

  if (hasTraveledFarEnough && hasHitVoltageThreshold) {
    servo.detach();
    return true;
  } else {
    servo.write(position);
  }

  delay(delayBetweenMoves);
  return false;
}

boolean isOpen(char* payloadText) {
  return strcmp(payloadText, "open") == 0;
}

boolean isClose(char* payloadText) {
  return strcmp(payloadText, "close") == 0;
}

boolean isOpened() {
  return currentPosition == openedPosition;
}

boolean isClosed() {
  return currentPosition == closedPosition;
}

void printMqttTopicValues() {
  Serial.print("MQTT_COMMAND_TOPIC: ");
  Serial.println(MQTT_COMMAND_TOPIC);
  Serial.print("MQTT_STATE_TOPIC: ");
  Serial.println(MQTT_STATE_TOPIC);
  Serial.print("MQTT_AVAILABILITY_TOPIC: ");
  Serial.println(MQTT_AVAILABILITY_TOPIC);
}
