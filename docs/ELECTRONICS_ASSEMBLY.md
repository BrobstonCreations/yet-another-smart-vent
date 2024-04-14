## Electronics Assembly
For a rough idea of how to do this, feel free to follow along in [this video which is pretty out of date](https://www.youtube.com/watch?v=D073FX6kdh8) and additionally read the written instructions below:

1. Snap off header pins from the header pin blocks that came with your components. You will need a header pin for 5V, GND, D3, D2, D1, A0, D5, D7, and 3V3.
2. I would recommend pressing these header pins into a breadboard (long side down) in the correct pattern for the above noted pins on the D1 Mini, this will make soldering the pins to the D1 mini much easier.
3. Press the D1 Mini on to the pins in the breadboard.
4. Solder the pins to the D1 Mini.
5. Once these pins are soldered, I would recommend removing the D1 Mini from the breadboard and clip it into a [third hand](https://en.wikipedia.org/wiki/Helping_hand_(tool)).
6. **OPTIONAL:** If you are planning to use [deep sleep functionality](https://esphome.io/components/deep_sleep.html) to save power, which is intended for battery use, you will need to cut a short length of wire, strip a small amount of insulation off each end, and from the bottom side of the board, solder **RST** to **D0**.
7. Now you should be able to press the DC Power Shield onto the pins you soldered to the D1 Mini. Be sure to insert the [spacer](https://www.printables.com/model/259295-esp-shield-solder-spacer) before soldering.
8. Solder the pins to the DC Power Shield.
9. Remove the spacer.
10. Cut the wires on the Servo Motor to a length of 2-2.5 inches.
11. Strip 1/4-3/8 of an inch of insulation off the end of each wire on the Servo Motor.
12. Tin the wires on the Servo Motor and each of the corresponding pins on the top of the Power Shield (5V, GND, D5, and A0).
13. Solder the wires to the top of the Power Shield:
    - DFRobot DMS-MG90-A: red (🟥) -> **5V**, black (⬛) -> **GND**, white (⬜) -> **D5**, and brown(🟫) -> **A0**.
    - Batan B2122: red (🟥) -> **5V**, brown (🟫) -> **GND**, yellow (🟨) -> **D5**, and white (⬜) -> **A0**.
14. Cut two of the left over wires to the length of 2-2.5 inches.
15. Strip 1/4-3/8 of an inch of insulation off both ends of each wire.
16. Tin the wires.
17. Insert the wires through the limit switch pin holes.
18. Solder the wires to the limit switch pins.
19. Solder the other ends to **D7** and **GND**. It does not matter which is connected to which. Note: You will now have two wires soldered to **GND**.
20. **OPTIONAL:** If you want to monitor temperature and humidity entering the room, you can add an [AHT10 Sensor](https://esphome.io/components/sensor/aht10.html). You will need to use some extra wire from the servo, cut four wires to 1.25-1.5 inches, strip a small amount of insulation off each end of each wire, and solder to make these connections: **VIN** -> **3V3**, **GND** -> **GND**, **SCL** -> **D1**, **SDA** -> **D2**. Note: You will now have three wires soldered to **GND**.
