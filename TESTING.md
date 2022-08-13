## Testing

[Short video demonstration on YouTube](https://youtu.be/ANneINQjgso)


In this example I will use the MQTT Integration in Home Assistant to test that my vent is working end-to-end.
1. Make sure you went through the previous steps to connect the vent to your WiFi and MQTT Broker.
2. When you power the vent on, after it successfully connects to WiFi it will go through a calibration step. It will turn to half open, then turn to closing endstop. This is determined by continuting to turn the louvers until the program no longer sees any changes from the servo's potentiometer; it will then record the position, turn back to half open, and repeat for the opening endstop.
3. Now we will test the MQTT side of things. Subscribe to the vent's state. When the state changes, the vent will publish `open`, `opening`, `closed`, or `closing`. For example, this message will be published on `stat/office/vent` if you set your `mqtt_topic` to `office/vent` in the setup.
4. Publish a message to the MQTT Broker. The vent will have subscribed to and will listen for `cmd/office/vent`, if you set your `mqtt_topic` to `office/vent` in the setup. Publish `close` to `cmd/office/vent`.
5. Assuming everything worked correctly, the vent should have moved to he closed state, and you should see `opening` and then `opened` published to `stat/office/vent`.
6. You can repeat step 3, except you will publish `open` to `cmd/office/vent`.
7. Assuming you then see `closing` and then `closed` published to `state/office/vent`, you're ready to use your vent.
