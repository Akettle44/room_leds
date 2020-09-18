#include <Arduino.h>
#include <FastLED.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB   
#define NUM_LEDS 160      //total number of leds (verified by multiplying amount of meters, 2.66, times 60 led per meter)
#define DATA_PIN 4        //data line
#define BRIGHTNESS 100    //scale down brightness to prevent current draw

//function decleration
void rainbow_fade();

//led array
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS); //initialzing strip 
  FastLED.setBrightness(BRIGHTNESS);
//fill_rainbow(&(leds[0]), NUM_LEDS, 0, 5);
//FastLED.show(); //write LEDs to strip
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
  
  //fade rainbow down, nested for rn, oof :(
  for(uint8_t n = 0; n < 255; n+=25) //255 is max brightness
  {
    for(uint8_t p = 0; p < NUM_LEDS; p++)
    {
      hsv = rgb2hsv_approximate((leds[p]));
      hsv.value -= 25;
      leds[p] = hsv;
    }
    FastLED.show(); //write LEDs to strip
    delay(50);
  }

  //fade rainbow back up, nested for rn, oof :(
  for(uint8_t m = 0; m < 255; m+=25) //255 is max brightness
  {
    for(uint8_t k = 0; k < NUM_LEDS; k++)
    {
      hsv = rgb2hsv_approximate((leds[k]));
      hsv.value += 25;
      leds[k] = hsv;
    }
    FastLED.show(); //write LEDs to strip
    delay(50);
  }
}