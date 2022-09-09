## Setup and Testing
  *In either of the first two options, you will need to go into your router/wifi/network device and find the IP address of your device*

  Control your device through its ESPHome Web Server:
  1. Navigate to the device by entering the IP address of the device into your web brower.
  2. The rest should be self-explanatory. There should be controls that correspond to the type ESPHome device you have configured.

  Control your device through Home Assistant:
  1. This device should show up automatically in your Home Assistant notifications and integrations. If it does not show up automatically, navigate to: Home Assistant -> Settings -> Devices & Services -> + Add Integration -> type "ESPHome" -> select "ESPHome" -> enter the IP address of your ESPHome device -> click "SUBMIT". You may need to go into your router/wifi/network device and find the IP address of your device.
  2. The rest should be self-explanatory. There should be controls that correspond to the type ESPHome device you have configured.
  
  Control your device using MQTT:
  1. Follow the steps for Install using ESPHome Dashboard in the [Compile and Upload](/docs/COMPILE_AND_UPLOAD.md) step.
  2. You will also need an MQTT Broker, [Everything Smart Home](https://www.youtube.com/c/EverythingSmartHome) has a good [MQTT Broker Setup Video](https://www.youtube.com/watch?v=dqTn-Gk4Qeo)
  3. Once your MQTT Broker is running, you will need to Integrate it with Home Assistant. Settings -> Devices & Services -> Click "+ ADD INTEGRATION" -> type "MQTT" -> click "MQTT" -> enter your MQTT configuration.
  4. In order to tell what topics/messages are being sent, you can navigate to: Settings -> Devices & Services -> click "CONFIGURE" on your MQTT Integration -> type "vent-living-room-southeast/#" in "Listen to topic" -> click "START LISTENING".
  5. This will display all topics/messages that are occuring for that vent. "#" is a wildcard.
  
