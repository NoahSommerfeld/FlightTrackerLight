# FlightTrackerLight
## Overview
The Flight Tracker Light uses a pre-built board consisting of an ESP32866 chip and a [pre-built array of LEDs](https://www.tindie.com/products/whalelec/nodeled/) to display notifications of a (configured) flight's arrival, departure, change, or cancellation, using FlightAware.com notificaiton emails as the notification source 'back end'. 

Ex. Flair Air (FLE) 223 Departing Toronto Pearson Airport (YYZ)

https://user-images.githubusercontent.com/7077613/147417214-a37b6d50-982f-4ed9-9e8b-4af7d633f5af.MOV

## Details and Examples
Overall flow: 
![image](https://user-images.githubusercontent.com/7077613/147722281-4dc9fc3b-21a4-43c0-87a2-36e9134121b1.png)

On boot, the board connects to the wifi network and logs in to the specific email account (all values per config.h) and monitors for new emails from alert@flightaware.com. Based on the content of the incoming email subject, the board displays one of five alerts:
- Departed (blue)
- Arrived (green)
- Changed/delayed/filed (yellow)
- Cancelled (red)
- Unknown alert (white with red question marks)

Some airlines/flight codes have been set to specific colors
- Westjet (WJA) - teal blue
- Air Canada (ACA) and Jazz Airlines (JZA) - red
- Flair Air (FLE) - purple
- Porter Airlines (POE) - dark blue
- Other (including private) - white

By default the board is set to look at the folder 'INBOX\FLIGHTAWARE'. It is recommended to have a rule set to auto-move emails from alert@flightaware.com to the subfolder to avoid other emails incidentally triggering an alert display




## Setup
### Prequisites: 
1. Have an email account set up with IMAP service, i.e an outlook.com or gmail account. Note that Gmail and [Outlook.com](https://support.microsoft.com/en-us/account-billing/using-app-passwords-with-apps-that-don-t-support-two-step-verification-5896ed9b-4263-e681-128a-a6f2979a7944) accounts with MFA require set up to enable application IMAP access. 
2. Set up alerts with a flightaware.com account set up with that email address

### Steps:
1. Set up the board connected to Power with a barrel-jack power adapter, and the PC via a data-capable micro USB-USB cable
2. In the Arduino IDE, add in the NODEMCU ESP8266 board as a compatible board https://www.instructables.com/Steps-to-Setup-Arduino-IDE-for-NODEMCU-ESP8266-WiF/
3. Add in the depedency libraries ([neopixelbus](https://www.arduino.cc/reference/en/libraries/neopixelbus-by-makuna/), [ESP32MailClient](https://www.arduino.cc/reference/en/libraries/esp32-mail-client/)) library via Arduino library manager (tools->Manager Library)
4. Clone the repository and open in Arduino IDE
5. Make a copy of the config-template.h file, rename it to just 'config.h', and then define the values for your personal setup (i.e wifi password, email settings, etc)
6. Upload FlightTrackerLight\FlightTrackerLight.ino to the board
7. When a flashed board receives power, it wil flash a dim white 'i' character until the wifi connects (usually 4-5 seconds). If this doesn't stop, it's likely incorrect wifi config values - check for errors via Serial connection

To easily see all types of notifications, uncomment line 130 and call the `alertHandleUnitTest()` function inside the main loop
