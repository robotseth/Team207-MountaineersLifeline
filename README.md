# **ASU EGR314 Team 207**
## Mountaineer's Lifeline

This is the code for the Mountaineer's Lifeline project for ERG314. This code is simplified from the initial plan and does not function fully as intended. It does, however, still have many of the main desired features.

The program consistently gathers heart rate data and calculates the user's heart rate from these readings. This is achieved using an interrupt that also blink the green debug LED. If this LED is blinking, that indicates that the heart rate is being measured.

To access the heart rate value the function ```avgHR()``` must be called. This function returns the last calculated heart rate. This is called by the main code loop and is used to send the heart rate value to an MQTT server on request. To request a heart rate, the letter ```a``` must be sent to the ```Team207\HeartRate\``` MQTT address. This will then be overwritten with the most up to date heart rate value by the mountaineer's lifeline device.

To use the MQTT server, the Wi-Fi settings set in the code for the ESP32 must be updated to match those of your network. Then, an application such as MQTT Explorer can be used to access the device.

**Authors:**
- Reagan Gillespie
- Seth Altobelli
- Danis Nugroho
- Max Gao
