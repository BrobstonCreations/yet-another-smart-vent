void saveConfig() {
  DynamicJsonDocument json(512);
  json["mqtt_server"] = mqtt_server;
  json["mqtt_port"] = mqtt_port;
  json["mqtt_username"] = mqtt_username;
  json["mqtt_password"] = mqtt_password;
  json["mqtt_topic"] = mqtt_topic;

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    return;
  }

  serializeJson(json, configFile);
  configFile.close();
}

void loadConfig() {
  if (SPIFFS.begin()) {
    if (SPIFFS.exists("/config.json")) {
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        const size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json(512);

        if (DeserializationError::Ok == deserializeJson(json, buf.get())) {
          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          strcpy(mqtt_username, json["mqtt_username"]);
          strcpy(mqtt_password, json["mqtt_password"]);
          strcpy(mqtt_topic, json["mqtt_topic"]);
        }
      }
    }
  }
}
