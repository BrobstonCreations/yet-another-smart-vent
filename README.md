# yet-another-smart-vent

This project contains most everything needed to 3D print, assemble, and flash an MQTT Smart Vent.

## Getting Started
1. Electronics
- Components
    - ESP8266 D1 Mini
    - DC Power Shield
    - Batan B2122
- Assembly
    - Make header pin sets for 5V, GND, D3, A0, and 3V3. The first four are needed, the 3V3 pin is just to add stability.
    - I would recommend pressing these header pins into a breadboard in the correct pattern for the above noted pins on the D1 Mini, this will make soldering the pins to the D1 mini much easier.
    - Once these 4 pins are soldered, I would recommend removing the D1 Mini from the breadboard and clip it into a third hard.
    - Now you should be able to press the DC Power Shield onto the pins. Be sure to insert the spacer, there will be an STL file provided to print this.
    - Solder the pins to the DC Power Shield.
    - Remove the spacer.
    - Cut the wires on the Batan B2122 to a length of 2-2.5 inches.
    - Strip the last 1/4-3/8 of an inch off the end of each wire on the Batan B2122.
    - Tin the wires on the Batan B2122 and each of the pins (5V, GND, D3, and A0).
    - Solder the red wire to 5V, the Brown wire to GND, the yellow wire to D3, and the white wire to A0.
2. 3D Printing
- Printing
- Assembly
3. Compile/Flash/Upload
4. Testing 

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

## Dependencies
- ArduinoJson 6.10.1
- PubSubClient 2.8.0
- WiFiManager 0.15.0
- DoubleResetDetector 1.0.3

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
