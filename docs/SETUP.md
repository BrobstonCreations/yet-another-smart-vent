## Setup  
  *In either of the first two options, you will need to go into your router/wifi/network device and find the IP address of your device*

  Control your device through its ESPHome Web Server:
  1. Navigate to the device by enter the IP address of the device into your web brower.
  2. The rest should be self-explanatory. There should be controls that correspond to the type ESPHome device you have configured.

  Control your device through Home Assistant:
  1. This device should show up automatically in your Home Assistant notifications and integrations. If it does not show up automatically, navigate to: Home Assistant -> Settings -> Devices & Services -> + Add Integration -> type "ESPHome" -> select "ESPHome" -> enter the IP address of your ESPHome device -> click "SUBMIT". You may need to go into your router/wifi/network device and find the IP address of your device.
  2. The rest should be self-explanatory. There should be controls that correspond to the type ESPHome device you have configured.
  
  Control your device using MQTT:
  1. Follow the steps for Install using ESPHome Dashboard in the [Compile and Upload](/docs/COMPILE_AND_UPLOAD.md) step.
