# Yet Another Smart Vent

This project contains most everything needed to 3D print, assemble, and flash an ESPHome/MQTT Smart Vent.

![PXL_20220812_211906955](https://user-images.githubusercontent.com/4724577/184465351-95fdbfe1-2a6a-43a4-8e92-827d9840c7b6.jpg)
[Here is a short video demonstration on YouTube.](https://youtu.be/ANneINQjgso) 
(Consider subscribing for future updates)

## Getting Started
1. Electronics:
    - Components:
        - D1 Mini ESP8266
        - D1 Mini DC Power Shield
        - Batan B2122
        - Power Source Options:
            - AC Adapter
            - Centralized Power Supply Components (consult an electrician if needed) (eventually I'll put out an STL for an enclosure for the Power Supply):
                - DC 24V15A 360W Switching Power Supply
                - [Power Supply Fused Power Injection Board](https://www.holidaycoro.com/product-p/1308.htm) (needs testing)
                - IEC Fused Power Socket and Switch
                - IEC Power Cable 5ft
                - Fork spade crimp terminals, fully insulated female spade terminal, and some stranded wire for load/neutral/ground between the IEC Socket and the Power Supply.
                - [Wiring to run through duct work](https://github.com/TonyBrobston/yet-another-smart-vent/issues/7#issuecomment-1221660336).
            - Battery Pack (not currently recommended, needs development for power saving mode).
    - [Assembly Instructions](/docs/ELECTRONICS_ASSEMBLY.md)
2. 3D Printing:
    - [Printing Advice](/docs/VENT_PRINTING.md)
    - [STLs](https://www.printables.com/social/337332-tonyb/collections/241144?o=download_count):
        - [2x10 Vent](https://www.printables.com/model/259777-yet-another-smart-vent-2x10)
        - [2x12 Vent](https://www.printables.com/model/260300-yet-another-smart-vent-2x12) (now with two-piece shell)
        - [3x10 Vent](https://www.printables.com/model/262311-yet-another-smart-vent-3x10) (needs testing)
        - [4x10 Vent](https://www.printables.com/model/259241-yet-another-smart-vent-4x10)
        - [4x12 Vent](https://www.printables.com/model/259924-yet-another-smart-vent-4x12) (now with two-piece shell)
        - [6x8 Vent](https://www.printables.com/model/264778-yet-another-smart-vent-6x8) (needs testing)
        - [6x10 Vent](https://www.printables.com/model/259323-yet-another-smart-vent-6x10)
        - [6x12 Vent](https://www.printables.com/model/259622-yet-another-smart-vent-6x12) (needs testing) (now with two-piece shell)
        - [ESP D1 Mini Shield Solder Spacer](https://www.printables.com/model/259295-esp-d1-mini-shield-solder-spacer)
    - [Assembly Instructions](/docs/VENT_ASSEMBLY.md)
3. [Compile and Upload Instructions](/docs/COMPILE_AND_UPLOAD.md)
4. [Setup and Testing](/docs/SETUP_AND_TESTING.md)
6. [Implementation Options](/docs/IMPLEMENTATION_OPTIONS.md)

## Important Recommendations 
- It is recommended to have a [Static Pressure Regulating Damper](https://www.zonefirst.com/product/sprddd/) installed between the main return and the main plenum. This will even out the static pressure that changes in the ducting, from opening or closing vents.
- If the previous recommendation is not possible, it may be possible to partially mitigate the static pressure issue by only closing vents (that are in a closed state) to something like 80% closed, when the number of closed vents is greater than, say... 75%. This will be a feature implemented in [mqtt-hvac-vent-control](https://github.com/TonyBrobston/mqtt-hvac-vent-control) in the future.
- It is recommended that you pair this vent with a system that can [measure and monitor Delta T](https://www.youtube.com/watch?v=_pD-rRCNv8k) (the difference in temperature of the air between the return plenum and the main plenum). Check out the [Delta Tango](https://github.com/BrobstonCreations/delta-tango) project (coming soon).

## Future Features
- Publish a distributable to Releases.
- Look into supporting [DMS-MG90-A](https://www.mouser.com/ProductDetail/DFRobot/SER0046?qs=vHuUswq2%252BsyGXvdy%2FXoNTA%3D%3D) Servo Motor.
- Fix a small bug where ESPHome's Servo Position does not match up with the Servo's Potentiometer's position.
- Test vents when furnace is heating. (I'm currently printing with [3DFuel Pro PLA+](https://www.3dfuel.com/collections/pro-pla/products/pro-pla-midnight-black-1-75mm) which should work just fine)
- Integrate a lever to manually open/close vent louvers.
- Investigate power saving options for battery pack use.
- Add functionality to open vent if the central vent control system goes offline.
- Experiment with 12x12 vent.

## Philosophy
- Local Control
- External Integration
- Easy of Use (with improvements over time)
- Community Feedback
- Community Contributions
- Agile, Lean, and Extreme Programming Practices
- Mostly Decentralized Manufacturing.

## Pull Requests
Pull Requests are always welcome. I would recommend starting with an [issue](https://github.com/TonyBrobston/yet-another-smart-vent/issues), so that we can discuss viability and implementation.

## Issues
Feel free to open an [issue](https://github.com/TonyBrobston/yet-another-smart-vent/issues) and I will respond as I have time. The hope is to create a system that gives consumers what they want, your feedback is important. 
