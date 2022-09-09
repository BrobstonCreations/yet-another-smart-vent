## Compile and Upload
This project uses ESPHome.

### Install Options:
  *Note: if you want to use MQTT, you will need to use the ESPHome Dashboard.*

  Flash device with `.bin` file:
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

Install using ESPHome Dashboard:
  1. You will need to have an ESPHome dashboard running. I use [their docker image](https://hub.docker.com/r/esphome/esphome), but there are other ways to get this running. I would recommend looking at [ESPHome's Getting Started](https://esphome.io/).
  2. Navigate to your ESPHome Dashboard.
  3. Click "+ NEW DEVICE".
  4. Click "CONTINE".
  5. Enter a name for the vent. It is recommended to use something like: `vent-living-room-southeast`.
  6. Choose "ESP8266".
  7. Click "INSTALL".
  8. Click "SKIP".
  9. Click "EDIT" on your newly created ESPHome configuration.
  10. Copy the configuration from [here](https://raw.githubusercontent.com/BrobstonCreations/yet-another-smart-vent/blob/master/yet_another_smart_vent.yaml) and paste it into the configuration code window.
  11. You will want to update a few values:
    - Change `name` to match the name of your device (aka `vent-living-room-southeast`).
    - Comment out `name_add_mac_suffix: true` if it is present.
    - I would recommend entering your `wifi_ssid` and `wifi_password` as secrets and comment in `ssid: !secret wifi_ssid` and `password: !secret wifi_password` and comment out `ap: {}`. You can also add a static ip, gateway, subnet; this makes devices reconnection faster as well as updates the "VISIT" button in the dashboard to use the device's IP address.
    - If you want to use MQTT, you can also comment those lines in and add your MQTT configuration values as secrets. If you use MQTT without Home Assistant, be sure to comment out `api:`.
   12. Click "INSTALL".
   13. Choose "Wirelessly" if your device is connected to the network; if not, I would recommend following one of the two "Plug into..." options.
   14. At this point your device should be finished installing and should appear on your ESPHome dashboard.

