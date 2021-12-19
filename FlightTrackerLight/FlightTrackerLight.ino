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

//Construct a RgbColor using R, G, B values (0-255). Color determined by mix, intensity by overall value.
//Note human eyes perceive logarithmcally so 10->20 much bigger change than 200->210. 
RgbColor throwaway = RgbColor(10,10,60);

//Board values
const uint16_t PixelCount = 46; // the number of pixeles in the strip
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

void setup() {
 // set board; resets all the neopixels to an off state 
    strip.Begin();
    strip.Show();
    
//set up wifi 

  //  updateBoard(RgbColor(0,0,0));
  
    //}
  //  updateBoard(RgbColor(0,0,0));
}

RgbColor indicatorColor = RgbColor(30,2,2);

void loop() {
  //light-up sequence
     strip.SetPixelColor(0,RgbColor(10,10,10));
     strip.Show();
     delay(750);
     strip.SetPixelColor(42,RgbColor(10,10,10));
     strip.Show();
     delay(750);
     strip.SetPixelColor(45,RgbColor(10,10,10));
     strip.Show();
     delay(750);
     strip.SetPixelColor(3,RgbColor(10,10,10));
     strip.Show();
     delay(1000);
      
     updateBoard(RgbColor(0,0,0));
  // put your main code here, to run repeatedly:
  //A
      strip.SetPixelColor(8,indicatorColor);
      strip.SetPixelColor(14,indicatorColor);
      strip.SetPixelColor(20,indicatorColor);
      strip.SetPixelColor(26,indicatorColor);
      strip.SetPixelColor(33,indicatorColor);
      strip.SetPixelColor(28,indicatorColor);
      strip.SetPixelColor(22,indicatorColor);
      strip.SetPixelColor(16,indicatorColor);
      strip.SetPixelColor(10,indicatorColor);
      strip.SetPixelColor(21,indicatorColor);
      

  //C
      strip.SetPixelColor(37,indicatorColor);
      strip.SetPixelColor(36,indicatorColor);
     // strip.SetPixelColor(35,indicatorColor);
      strip.SetPixelColor(29,indicatorColor);
      strip.SetPixelColor(23,indicatorColor);
      strip.SetPixelColor(17,indicatorColor);
     // strip.SetPixelColor(11,indicatorColor);
      strip.SetPixelColor(12,indicatorColor);
      strip.SetPixelColor(13,indicatorColor);
      strip.Show();
      delay ( 1800 );
      
     updateBoard(RgbColor(0,0,0));
// 1
     strip.SetPixelColor(29,indicatorColor);
     strip.SetPixelColor(36,indicatorColor);
     strip.SetPixelColor(30,indicatorColor);
     strip.SetPixelColor(24,indicatorColor);
     strip.SetPixelColor(18,indicatorColor);
     strip.SetPixelColor(12,indicatorColor);
     strip.SetPixelColor(11,indicatorColor);
     strip.SetPixelColor(13,indicatorColor);
     strip.Show();
     delay ( 1200 );
     updateBoard(RgbColor(0,0,0));

// 2
    // 1
     strip.SetPixelColor(26,indicatorColor);
     strip.SetPixelColor(33,indicatorColor);
     strip.SetPixelColor(27,indicatorColor);
     strip.SetPixelColor(21,indicatorColor);
     strip.SetPixelColor(15,indicatorColor);
     strip.SetPixelColor(9,indicatorColor);
     strip.SetPixelColor(8,indicatorColor);
     strip.SetPixelColor(10,indicatorColor);

     //2
     strip.SetPixelColor(29,indicatorColor);
     strip.SetPixelColor(36,indicatorColor);
     strip.SetPixelColor(31,indicatorColor);
     strip.SetPixelColor(24,indicatorColor);
     strip.SetPixelColor(17,indicatorColor);
     strip.SetPixelColor(11,indicatorColor);
     strip.SetPixelColor(12,indicatorColor);
     strip.SetPixelColor(13,indicatorColor);
     strip.Show();
     delay (1200 );
     updateBoard(RgbColor(0,0,0));

// 4
    //2
     strip.SetPixelColor(26,indicatorColor);
     strip.SetPixelColor(33,indicatorColor);
     strip.SetPixelColor(28,indicatorColor);
     strip.SetPixelColor(21,indicatorColor);
     strip.SetPixelColor(14,indicatorColor);
     strip.SetPixelColor(8,indicatorColor);
     strip.SetPixelColor(9,indicatorColor);
     strip.SetPixelColor(10,indicatorColor);


    //4
    strip.SetPixelColor(35,indicatorColor);
    strip.SetPixelColor(29,indicatorColor);
    strip.SetPixelColor(23,indicatorColor);
    strip.SetPixelColor(24,indicatorColor);
    strip.SetPixelColor(25,indicatorColor);
    strip.SetPixelColor(37,indicatorColor);
    strip.SetPixelColor(31,indicatorColor);
    strip.SetPixelColor(19,indicatorColor);
    strip.SetPixelColor(13,indicatorColor);
    strip.Show();
    delay ( 1200 );
      
    updateBoard(RgbColor(0,0,0));
    strip.Show();
    delay ( 1200 );
    
 //AR
    //A
      strip.SetPixelColor(8,indicatorColor);
      strip.SetPixelColor(14,indicatorColor);
      strip.SetPixelColor(20,indicatorColor);
      strip.SetPixelColor(26,indicatorColor);
      strip.SetPixelColor(33,indicatorColor);
      strip.SetPixelColor(28,indicatorColor);
      strip.SetPixelColor(22,indicatorColor);
      strip.SetPixelColor(16,indicatorColor);
      strip.SetPixelColor(10,indicatorColor);
      strip.SetPixelColor(21,indicatorColor);
 
    //R
      strip.SetPixelColor(35,indicatorColor);
      strip.SetPixelColor(29,indicatorColor);
      strip.SetPixelColor(23,indicatorColor);
      strip.SetPixelColor(17,indicatorColor);
      strip.SetPixelColor(11,indicatorColor);
      strip.SetPixelColor(36,indicatorColor);
      strip.SetPixelColor(31,indicatorColor);
      strip.SetPixelColor(24,indicatorColor);
      strip.SetPixelColor(19,indicatorColor);
      strip.SetPixelColor(13,indicatorColor);
      strip.Show();
      delay ( 1200 );
       updateBoard(RgbColor(0,0,0));
    strip.Show();
    delay ( 1200 );

//yyz

  //Y
      strip.SetPixelColor(35,indicatorColor);
      strip.SetPixelColor(29,indicatorColor);
      strip.SetPixelColor(24,indicatorColor);
      strip.SetPixelColor(37,indicatorColor);
      strip.SetPixelColor(31,indicatorColor);
      strip.SetPixelColor(18,indicatorColor);
      strip.SetPixelColor(12,indicatorColor);
      strip.Show();
      delay (1200 );
      updateBoard(RgbColor(0,0,0));

  //YY
      strip.SetPixelColor(35,indicatorColor);
      strip.SetPixelColor(29,indicatorColor);
      strip.SetPixelColor(24,indicatorColor);
      strip.SetPixelColor(37,indicatorColor);
      strip.SetPixelColor(31,indicatorColor);
      strip.SetPixelColor(18,indicatorColor);
      strip.SetPixelColor(12,indicatorColor);

      strip.SetPixelColor(32,indicatorColor);
      strip.SetPixelColor(26,indicatorColor);
      strip.SetPixelColor(21,indicatorColor);
      strip.SetPixelColor(34,indicatorColor);
      strip.SetPixelColor(28,indicatorColor);
      strip.SetPixelColor(15,indicatorColor);
      strip.SetPixelColor(9,indicatorColor);
      strip.Show();
      delay (1200 );
      updateBoard(RgbColor(0,0,0));

  //YZ
      strip.SetPixelColor(32,indicatorColor);
      strip.SetPixelColor(26,indicatorColor);
      strip.SetPixelColor(21,indicatorColor);
      strip.SetPixelColor(34,indicatorColor);
      strip.SetPixelColor(28,indicatorColor);
      strip.SetPixelColor(15,indicatorColor);
      strip.SetPixelColor(9,indicatorColor);

      strip.SetPixelColor(35,indicatorColor);
      strip.SetPixelColor(36,indicatorColor);
      strip.SetPixelColor(37,indicatorColor);
      strip.SetPixelColor(31,indicatorColor);
      strip.SetPixelColor(24,indicatorColor);
      strip.SetPixelColor(17,indicatorColor);
      strip.SetPixelColor(11,indicatorColor);
      strip.SetPixelColor(12,indicatorColor);
      strip.SetPixelColor(13,indicatorColor);
      strip.Show();
      delay (1200 );
      updateBoard(RgbColor(0,0,0));
      delay (1800 );
}

void updateBoard(RgbColor colorToSet){
    for (uint16_t i = 0; i < PixelCount; i += 1)
        {
            strip.SetPixelColor(i, colorToSet);
        }

   strip.Show();
}
