## Compile and Upload
Eventually I'll move this project to use [PlatformIO](https://platformio.org/), but for now you will need to install dependencies, compile, and flash manually. This is easier then I originally thought, but requires the Arduino IDE.

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Open `yet_another_smart_vent`.
![1-open-project-in-arduino-ide](https://user-images.githubusercontent.com/4724577/184546875-843e9e3f-1aba-46c1-abf2-17a903b34bd5.png)
3. Install "Additional Boards Manager URLs". File > Preferences. Add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` to "Additional Boards Manager URLs". If there is more than one, add a command in between (`,`). Click "OK".
4. Select the correct board. Tools > Board > ESP8266 Board > Generic ESP8266 Module.
5. Select the correct port. Tools > Port. On Linux this will be something like `/dev/ttyUSB0`, on Windows it will probably be something else.
6. Install the few libraries that are required. Tools > Manage Libraries.
![2-open-manage-libraries](https://user-images.githubusercontent.com/4724577/184547065-ed91cf55-c1cf-47e8-b1eb-d43fd1830433.png)
7. Search for the Dependencies listed in the [main README](/README.md), select the correct version, and install. Repeat for all dependencies listed.
![3-search-for-dependency-select-version-and-install](https://user-images.githubusercontent.com/4724577/184547098-8651182c-6294-4bf6-acbf-b583bdf46c55.png)
8. You should now be ready to Compile/Upload. Be sure the ESP8266 D1 Mini is connected and click "Upload" button (right arrow circle).
![4-compile-and-upload](https://user-images.githubusercontent.com/4724577/184547135-c7d94468-5f53-41a3-a154-10e2e9e69214.png)
9. Alternatively it is also possible to compile and upload from command line:
    
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
