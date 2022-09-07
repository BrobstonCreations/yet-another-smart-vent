## Implementation Options

1. Home Assistant MQTT Cover. This device should show up automatically in your Home Assistant notifications and integrations. If it does not show up automatically, navigate to: Home Assistant -> Settings -> Devices & Services -> + Add Integration -> type "ESPHome" -> select "ESPHome" -> enter the IP address of your ESPHome device -> click "SUBMIT". You may need to go into your router/wifi/network device and find the IP address of your device.
2. [MQTT HVAC Vent Control](https://github.com/TonyBrobston/mqtt-hvac-vent-control)
    - This system is integrations a thermostat, temperature sensors, and smart vents.
    - This system is experimental and will likely move to a Home Assistant Integration in the future.
    - This system requires MQTT. You will have to load up an ESPHome Dashboard, adopt the device, and edit the configuration to enter your [MQTT configuration values](https://esphome.io/components/mqtt.html).


*If you know of some other options, feel free to add them here.*
