#include "Config.h"
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//************ GLOBAL VALUES ********************
//Wifi values
const char *ssid     = CONFIG_WIFI_SSID; //pulled from Config file - update to your implementation
const char *password = CONFIG_WIFI_PASSWORD;
WiFiUDP ntpUDP;

//Board values
const uint16_t PixelCount = 46; // the number of pixeles in the strip
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

void setup() {
 // set board; resets all the neopixels to an off state 
    strip.Begin();
    strip.Show();
    
//set up wifi 
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  //  updateBoard(RgbColor(0,0,0));
    while ( WiFi.status() != WL_CONNECTED ) { 
      strip.SetPixelColor(5,RgbColor(10,10,10)); //indicator LED to confirm power and Wifi connection
      strip.Show();
      delay ( 250 );
      Serial.print ( "." );
      strip.SetPixelColor(5,RgbColor(0,0,0));
      strip.Show();
      delay (250);
    }
  //  updateBoard(RgbColor(0,0,0));
}

void loop() {
  // put your main code here, to run repeatedly:
      strip.SetPixelColor(10,RgbColor(10,10,60)); 
      strip.Show();
      delay ( 250 );
      strip.SetPixelColor(10,RgbColor(0,0,0));
      strip.Show();
      delay (250);
}
