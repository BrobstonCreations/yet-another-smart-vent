## Compile and Upload Written Instructions

1. Download the `.bin` file that you want to flash from [Releases](https://github.com/TonyBrobston/yet-another-smart-vent/releases).
2. Plug a micro-usb cable into your ESP8266 D1 Mini (usb port on the bottom of the vent). It is important that you use a micro-usb data cable, not one that is for only power/charging.
3. Open https://web.esphome.io
4. Click `CONNECT`.
5. Select your Serial Port in the browser modal that opened at the end of the previous step.
6. Click `Connect`.
7. Click `INSTALL`.
8. Click `Choose File`.
9. Select the `.bin` file you downloaded in step #1.
10. Click `INSTALL`.
11. The install should begin. You will likely have to "Keep this page visible to prevent slow down".
12. Soon after your flash finishes, the D1 Mini should broadcast a WiFi access point as the name from the configuration followed by the beginning of the device's MAC address (ex: `yet-another-smart-vent-122de8`).
13. Connect to this WiFi access point.
14. A Captive Portal should open automatically. If it does not, navigate to 192.168.4.1 in your browser.
15. Enter the WiFi SSID/Password of the 2.4 GHz wireless network that you would like this device to connect to. 
