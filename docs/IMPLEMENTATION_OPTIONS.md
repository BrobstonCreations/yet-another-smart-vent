## Implementation Options
1. [MQTT HVAC Vent Control](https://github.com/TonyBrobston/mqtt-hvac-vent-control)
    - This system is integrations a thermostat, temperature sensors, and smart vents.
2. Home Assistant [MQTT Cover](https://www.home-assistant.io/integrations/cover.mqtt/)
    - This simply allows you to manually open/close a smart vent. This can be helpful for troubleshooting.
    ```
    cover:
      - platform: mqtt
        unique_id: office_vent
        name: Office Vent
        command_topic: cmd/office/vent
        payload_open: open
        payload_close: close
        payload_stop:
        state_topic: stat/office/vent
        state_open: opened
        availability_topic: tele/office/vent/LWT
        device_class: damper
    ```

*If you know of some other options, feel free to add them here.*
