#include "Config.h"
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>


//************ GLOBAL VALUES ********************
//Wifi values
const char *ssid     = CONFIG_WIFI_SSID; //pulled from Config file - update to your implementation
const char *password = CONFIG_WIFI_PASSWORD;

//Board values
const uint16_t PixelCount = 46; // the number of pixeles in the strip
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

void setup() {
 // set board; resets all the neopixels to an off state 
    strip.Begin();
    strip.Show();

}

void loop() {
  // put your main code here, to run repeatedly:
      strip.SetPixelColor(5,RgbColor(10,10,10)); //indicator LED to confirm power and Wifi connection
      strip.Show();
      delay ( 250 );
      strip.SetPixelColor(5,RgbColor(0,0,0));
      strip.Show();
      delay (250);
}
