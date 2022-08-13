# Yet Another Smart Vent

This project contains most everything needed to 3D print, assemble, and flash an MQTT Smart Vent.

![PXL_20220812_211906955](https://user-images.githubusercontent.com/4724577/184465351-95fdbfe1-2a6a-43a4-8e92-827d9840c7b6.jpg)

## Getting Started
1. Electronics
    - Components
        - ESP8266 D1 Mini
        - DC Power Shield
        - Batan B2122
        - Power Source Options
            - AC Adapter
            - Centralized 24V Power Supply
            - Battery Pack (needs development for power saving mode).
    - [Assembly Instructions](/docs/ELECTRONICS_ASSEMBLY.md)
2. 3D Printing
    - [Printing Advice](/docs/VENT_PRINTING.md)
    - [Assembly Pictures](/docs/VENT_ASSEMBLY.md)
3. Compile/Upload
    - TODO: Add Instructions
    - Dependencies
        - ArduinoJson 6.10.1
        - PubSubClient 2.8.0
        - WiFiManager 0.15.0
        - DoubleResetDetector 1.0.3
4. MQTT Broker
    - [Everything Smart Home](https://www.youtube.com/c/EverythingSmartHome) has a good [MQTT Broker Setup Video](https://www.youtube.com/watch?v=dqTn-Gk4Qeo).
5. [Setup](/docs/SETUP.md)
6. [Testing](/docs/TESTING.md) 

## Future Features
- Investigate power saving options for battery pack use.
- Subscribe to an MQTT topic to clear the configuration.
- Subscribe to an MQTT topic to rerun the initial open/close calibration.
- Subscribe to an MQTT topic published by the central vent system to open the vent when that system is offline.
- Publish automatic configuration. [example](https://github.com/Hypfer/esp8266-midea-dehumidifier/blob/ff869266c660657da25dc90e801d583ad34b6a8d/src/esp8266-midea-dehumidifier/esp8266-midea-dehumidifier.ino#L270)
- Publish debug information to an MQTT topic for easier troubleshooting.
- Add retain as an option to initial WiFi/MQTT setup.
- Implement ArduinoOTA.
- Update repo to use latest dependencies.

## Philosophy

## Pull Requests

## Bugs

## Development
To compile from command line:
`arduino-cli compile --fqbn esp8266:esp8266:d1 yet_another_smart_vent`

To upload from command line:
`arduino-cli upload -p /dev/ttyUSB0 --fqbn esp8266:esp8266:d1 yet_another_smart_vent`

To monitor serial output from command line:
```
sudo apt-get install minicom
minicom -D /dev/ttyUSB0 -b 9600
```
`CTRL-A` then  `x` to exit.

## References
This repo is a modifcation of [Hypfer's Midea Dehumidifier](https://github.com/Hypfer/esp8266-midea-dehumidifier).
