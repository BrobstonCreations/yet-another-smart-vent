# yet-another-smart-vent

This project contains most everything needed to 3D print, assemble, and flash an MQTT Smart Vent.

## Getting Started
1. Electronics
    - Components
        - ESP8266 D1 Mini
        - DC Power Shield
        - Batan B2122
    - Assembly
        1. Snap off header pins from one of the header pin blocks that came with your components. You will need a header pin for 5V, GND, D3, A0, and 3V3. The first four are needed, the 3V3 pin is just to add stability between the D1 Mini and the DC Power Shield.
        2. I would recommend pressing these header pins into a breadboard in the correct pattern for the above noted pins on the D1 Mini, this will make soldering the pins to the D1 mini much easier.
        3. Press the D1 Mini on to the pins in the breadboard.
        4. Solder the pins to the D1 Mini.
        5. Once these pins are soldered, I would recommend removing the D1 Mini from the breadboard and clip it into a third hard.
        6. Now you should be able to press the DC Power Shield onto the pins you soldered to the D1 Mini. Be sure to insert the spacer, there will be an STL file provided to print this; this is also pictured in the Assembly instructions.
        7. Solder the pins to the DC Power Shield.
        8. Remove the spacer.
        9. Cut the wires on the Batan B2122 to a length of 2-2.5 inches.
        10. Strip 1/4-3/8 of an inch of insulation off the end of each wire on the Batan B2122.
        11. Tin the wires on the Batan B2122 and each of the pins (5V, GND, D3, and A0).
        12. Solder the red wire to 5V, the Brown wire to GND, the yellow wire to D3, and the white wire to A0.
2. 3D Printing
    - [Printing Advice](/VENT_PRINTING.md)
    - [Assembly Pictures](/VENT_ASSEMBLY.md)
3. Compile/Flash/Upload/Dependencies
    - ArduinoJson 6.10.1
    - PubSubClient 2.8.0
    - WiFiManager 0.15.0
    - DoubleResetDetector 1.0.3
4. [Setup](/SETUP.md)
5. [Testing](/TESTING.md) 

## Future features
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
