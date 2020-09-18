#include <Arduino.h>
#include <FastLED.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB   
#define NUM_LEDS 160      //total number of leds (verified by multiplying amount of meters, 2.66, times 60 led per meter)
#define DATA_PIN 4        //data line
#define BRIGHTNESS 200    //scale down brightness to prevent current draw

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS); //initialzing strip 
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  rainbow_fade();
}

void rainbow_fade()
{
  //intialize hsv values
  CHSV hsv;
  hsv.hue = 0; //starts at 0 
  hsv.saturation = 255;
  hsv.value = 255;

  //display the rainbow
  for(uint8_t i = 0; i < NUM_LEDS; i++)
  {
    hsv.hue = 255 * sin8_avr(millis()); //using past milliseconds and scaling between [0,1]
    leds[i] = hsv; 
  }
  FastLED.show(); //write LEDs to strip
  
  //fade rainbow down
  for(uint8_t j = 255; j > 0; j--)
  {
    hsv.value -= 25;
    delay(10);
    FastLED.show(); //write LEDs to strip
  }

  //fade rainbow back up
  for(uint8_t m = 0; m < 255; m++) //255 is max brightness
  {
    for(uint8_t k = 0; k < NUM_LEDS; k++)
    {
      //how to get the current value for an hsv
    }
    FastLED.show(); //write LEDs to strip
    delay(2);
  }

  FastLED.show(); //write LEDs to strip

}