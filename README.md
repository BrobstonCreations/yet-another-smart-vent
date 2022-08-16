# Yet Another Smart Vent

This project contains most everything needed to 3D print, assemble, and flash an MQTT Smart Vent.

![PXL_20220812_211906955](https://user-images.githubusercontent.com/4724577/184465351-95fdbfe1-2a6a-43a4-8e92-827d9840c7b6.jpg)
[Here is a short video demonstration on YouTube.](https://youtu.be/ANneINQjgso)

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
    - STLs
        - [2x10 Vent](https://www.printables.com/model/259777-yet-another-smart-vent-2x10) (testing at the moment)
        - [4x10 Vent](https://www.printables.com/model/259241-yet-another-smart-vent-4x10)
        - [4x12 Vent](https://www.printables.com/model/259924-yet-another-smart-vent-4x12) (needs testing)
        - [6x10 Vent](https://www.printables.com/model/259323-yet-another-smart-vent-6x10)
        - [6x12 Vent](https://www.printables.com/model/259622-yet-another-smart-vent-6x12) (needs testing)
    - [Printing Advice](/docs/VENT_PRINTING.md)
    - [Assembly Instructions](/docs/VENT_ASSEMBLY.md)
3. [Compile and Upload Instructions](/docs/COMPILE_AND_UPLOAD.md)
4. MQTT Broker
    - [Everything Smart Home](https://www.youtube.com/c/EverythingSmartHome) has a good [MQTT Broker Setup Video](https://www.youtube.com/watch?v=dqTn-Gk4Qeo).
5. [Setup](/docs/SETUP.md)
6. [Testing](/docs/TESTING.md)
7. [Implementation Options](/docs/IMPLEMENTATION_OPTIONS.md)

## Future Features
- Create more vent variations (2x12 and 6x14?).
- Make open/close calibration slightly less sensitive.
- Integrate a lever to manually open/close vent louvers.
- Investigate power saving options for battery pack use.
- Investigate ESPHome as a potential option to decrease this project's complexity.
- Subscribe to an MQTT topic to clear the configuration.
- Subscribe to an MQTT topic to rerun the initial open/close calibration.
- Subscribe to an MQTT topic published by the central vent system to open the vent when that system is offline.
- Publish automatic configuration. [example](https://github.com/Hypfer/esp8266-midea-dehumidifier/blob/ff869266c660657da25dc90e801d583ad34b6a8d/src/esp8266-midea-dehumidifier/esp8266-midea-dehumidifier.ino#L270)
- Publish debug information to an MQTT topic for easier troubleshooting.
- Add retain as an option to initial WiFi/MQTT setup.
- Implement ArduinoOTA.
- Update repo to use latest dependencies.
- Use PlatformIO for dependencies.
- Publish a distributable to Releases.

## Philosophy
- Local Control
- External Integration
- Easy of Use (this will improve over time)
- Community Feedback
- Community Contributions
- Agile, Lean, and Extreme Programming Practices
- Test Driven Development (hopefully in the future)
- Mostly Decentralized Manufacturing.

## Pull Requests
Pull Requests are always welcome. I would recommend starting with an [issue](https://github.com/TonyBrobston/yet-another-smart-vent/issues), so that we can discuss viability and implementation.

## Issues
Feel free to open an [issue](https://github.com/TonyBrobston/yet-another-smart-vent/issues) and I will respond as I have time. The hope is to create a system that gives consumers what they want, your feedback is important. 

## References
This repo is a modifcation of [Hypfer's Midea Dehumidifier](https://github.com/Hypfer/esp8266-midea-dehumidifier).
