# Yet Another Smart Vent

This project contains most everything needed to 3D print, assemble, and flash an ESPHome/MQTT Smart Vent.

![PXL_20220812_211906955](https://user-images.githubusercontent.com/4724577/184465351-95fdbfe1-2a6a-43a4-8e92-827d9840c7b6.jpg)
[Here is a short video demonstration on YouTube.](https://youtu.be/ANneINQjgso) 
(Consider subscribing for future updates)

## Getting Started
1. Electronics:
    - Components:
        - [Components Kits](https://brobston-creations.mybigcommerce.com/yet-another-smart-vent-electronics-and-fasteners-kit/)
        - [Components List](/docs/ELECTRONIC_COMPONENTS.md)
    - [Assembly Instructions](/docs/ELECTRONICS_ASSEMBLY.md)
2. 3D Printing:
    - [Printing Advice](/docs/VENT_PRINTING.md)
    - [STLs](https://www.printables.com/social/337332-tonyb/collections/241144?o=download_count):
        - [2x10 Vent](https://www.printables.com/model/259777-yet-another-smart-vent-2x10)
        - [2x12 Vent](https://www.printables.com/model/260300-yet-another-smart-vent-2x12)
        - [3x10 Vent](https://www.printables.com/model/262311-yet-another-smart-vent-3x10)
        - [4x10 Vent](https://www.printables.com/model/259241-yet-another-smart-vent-4x10)
        - [4x12 Vent](https://www.printables.com/model/259924-yet-another-smart-vent-4x12)
        - [4x14 Vent](https://www.printables.com/model/334635-yet-another-smart-vent-4x14)
        - [6x8   Vent](https://www.printables.com/model/264778-yet-another-smart-vent-6x8)
        - [6x10 Vent](https://www.printables.com/model/259323-yet-another-smart-vent-6x10)
        - [6x12 Vent](https://www.printables.com/model/259622-yet-another-smart-vent-6x12)
        - [ESP D1 Mini Shield Solder Spacer](https://www.printables.com/model/259295-esp-d1-mini-shield-solder-spacer)
    - [Assembly Instructions](/docs/VENT_ASSEMBLY.md)
3. [Compile and Upload Instructions](/docs/COMPILE_AND_UPLOAD.md)
4. [Setup and Testing](/docs/SETUP_AND_TESTING.md)
6. [Implementation Options](/docs/IMPLEMENTATION_OPTIONS.md)

## Important Recommendations
- It is recommended that you pair this vent with a system that can [measure and monitor Delta T](https://www.youtube.com/watch?v=_pD-rRCNv8k) (the difference in HVAC return air temperature and supply air temperature). Check out the [Delta Tango](https://github.com/BrobstonCreations/delta-tango) project.
- It is recommended to have a [Static Pressure Regulating Damper](https://www.zonefirst.com/product/sprddd/) installed between the return air plenum and the supply air plenum. This regulating damper acts as a bypass and will open or close relative to the backpressure change created by opening or closing vents. This will relieve the majority of the back pressure that is created by closing vents and will help to ensure the longevity of the blower.
- If the previous recommendation is not possible, it may be possible to partially mitigate the static pressure issue by only closing vents (that are in a closed state) to something like 80% closed, when the number of closed vents is greater than, say... 75%. This will be a feature implemented in [mqtt-hvac-vent-control](https://github.com/TonyBrobston/mqtt-hvac-vent-control) in the future.

## Future Features
- Create 2x6 vent variation.
- Experiment with adding heat set inserts rather than threading into plastic.
- Fix a small bug where ESPHome's Servo Position does not match up with the Servo's Potentiometer's position after physically moving the vent's louvers.
- Test vents when furnace is heating. (I'm currently printing with.
- Integrate a lever to manually open/close vent louvers. (currently in development)
- Investigate power saving options for battery pack use.
- Add functionality to open vent if the central vent control system goes offline.
- Experiment with 12x12 vent.

## Philosophy
- Local Control
- External Integration
- Easy of Use
- Community Feedback
- Community Contributions
- Agile, Lean, and Extreme Programming Practices
- Mostly Decentralized Manufacturing

## Pull Requests
Pull Requests are always welcome. I would recommend starting with an [issue](https://github.com/TonyBrobston/yet-another-smart-vent/issues), so that we can discuss viability and implementation.

## Issues
Feel free to open an [issue](https://github.com/TonyBrobston/yet-another-smart-vent/issues) and I will respond as I have time. The hope is to create a system that gives consumers what they want, your feedback is important. 

## Support
If you like the work I do and want to give back, consider [buying me a coffee ☕](https://www.buymeacoffee.com/brocreates) or making a donation via [PayPal](https://www.paypal.com/donate/?hosted_button_id=BXK8JW6A2FZLE) or [Stripe](https://buy.stripe.com/7sI7t03JC9GUf4c6oo).
