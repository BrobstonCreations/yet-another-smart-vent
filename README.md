# Yet Another Smart Vent

This project contains most everything needed to 3D print, assemble, and flash an MQTT Smart Vent.

![PXL_20220812_211906955](https://user-images.githubusercontent.com/4724577/184465351-95fdbfe1-2a6a-43a4-8e92-827d9840c7b6.jpg)
[Here is a short video demonstration on YouTube.](https://youtu.be/ANneINQjgso) 
(Consider subscribing for future updates)

## Getting Started
1. Electronics
    - Components
        - D1 Mini ESP8266
        - D1 Mini DC Power Shield
        - Batan B2122
        - Power Source Options
            - AC Adapter
            - Centralized 24V Power Supply
            - Battery Pack (needs development for power saving mode).
    - [Assembly Instructions](/docs/ELECTRONICS_ASSEMBLY.md)
2. 3D Printing
    - [Printing Advice](/docs/VENT_PRINTING.md)
    - [STLs](https://www.printables.com/social/337332-tonyb/collections/241144)
        - [2x10 Vent](https://www.printables.com/model/259777-yet-another-smart-vent-2x10)
        - [2x12 Vent](https://www.printables.com/model/260300-yet-another-smart-vent-2x12) (now with two-piece shell)
        - [3x10 Vent](https://www.printables.com/model/262311-yet-another-smart-vent-3x10) (needs testing)
        - [4x10 Vent](https://www.printables.com/model/259241-yet-another-smart-vent-4x10)
        - [4x12 Vent](https://www.printables.com/model/259924-yet-another-smart-vent-4x12) (testing currently) (now with two-piece shell)
        - [6x8 Vent](https://www.printables.com/model/264778-yet-another-smart-vent-6x8) (needs testing)
        - [6x10 Vent](https://www.printables.com/model/259323-yet-another-smart-vent-6x10)
        - [6x12 Vent](https://www.printables.com/model/259622-yet-another-smart-vent-6x12) (needs testing) (now with two-piece shell)
        - [ESP D1 Mini Shield Solder Spacer](https://www.printables.com/model/259295-esp-d1-mini-shield-solder-spacer)
    - [Assembly Instructions](/docs/VENT_ASSEMBLY.md)
3. [Compile and Upload Instructions](/docs/COMPILE_AND_UPLOAD.md)
4. MQTT Broker
    - [Everything Smart Home](https://www.youtube.com/c/EverythingSmartHome) has a good [MQTT Broker Setup Video](https://www.youtube.com/watch?v=dqTn-Gk4Qeo).
5. [Setup](/docs/SETUP.md)
6. [Testing](/docs/TESTING.md)
7. [Implementation Options](/docs/IMPLEMENTATION_OPTIONS.md)

## Other Notes
- It is recommended to have a [Static Pressure Regulating Damper](https://www.zonefirst.com/product/sprddd/) installed between the main return and the main plenum. This will even out the static pressure that changes in the ducting, from opening or closing vents.
- If the previous recommendation is not possible, it may be possible to partially mitigate the static pressure issue by only closing vents (that are in a closed state) to 80% closed, when the number of closed vents is greater than 75%. This will be a feature implemented in [mqtt-hvac-vent-control](https://github.com/TonyBrobston/mqtt-hvac-vent-control) in the future.

## Future Features
- Make open/close calibration slightly less sensitive.
- Add the ability to move the vent to a specific position between 0% and 100%.
- Investigate ESPHome as a potential option to decrease this project's complexity.
- Test vents when furnace is heating. (I'm currently printing with [3DFuel Pro PLA+](https://www.3dfuel.com/collections/pro-pla/products/pro-pla-midnight-black-1-75mm) which should work just fine)
- Integrate a lever to manually open/close vent louvers.
- Investigate power saving options for battery pack use.
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
- Experiment with 12x12 vent.

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
