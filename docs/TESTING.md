## Testing

[Short video demonstration on YouTube](https://youtu.be/ANneINQjgso)


In this example I will use the MQTT Integration in Home Assistant to test that my vent is working end-to-end.
1. Be sure to have gone through the previous steps to connect the vent to your WiFi and MQTT Broker.
2. When you power the vent on, after it successfully connects to WiFi it will go through a calibration step. It will turn to half open, then turn to closing endstop. This is determined by continuting to turn the louvers until the program no longer sees any changes from the servo's potentiometer; it will then record the position, turn back to half open, and repeat for the opening endstop.
3. Now we will test the MQTT side of things. Subscribe to the vent's state. When the state changes, the vent will publish `open`, `opening`, `closed`, or `closing`. For example, this message will be published on `stat/office/vent` if you set your `mqtt_topic` to `office/vent` in the setup.

![image](https://user-images.githubusercontent.com/4724577/184465255-e21ebf35-4800-4758-9e98-7b0005417a44.png)

5. Publish a message to the MQTT Broker. The vent will have subscribed to and will listen for `cmd/office/vent`, if you set your `mqtt_topic` to `office/vent` in the setup. Publish `close` to `cmd/office/vent`.

![image](https://user-images.githubusercontent.com/4724577/184465282-83f86652-212e-4f67-b36f-f6f1d121872e.png)

6. Assuming everything worked correctly, the vent should have moved to closed, and you should see `closing` and then `closed` published to `stat/office/vent`.

![image](https://user-images.githubusercontent.com/4724577/184465294-9862714b-204f-4bc1-a7b3-f47cd7476651.png)

7. You can repeat step 3, except you will publish `open` to `cmd/office/vent`.
8. Assuming you then see `opening` and then `opened` published to `state/office/vent`, you're ready to use your vent.
