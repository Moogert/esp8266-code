#include <stdio.h>
#include <math.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 14
#define PI 3.14159265
uint16_t mod2 = 0;
uint16_t mod1 = 0;
uint16_t i = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);
uint32_t purple = strip.Color(4, 0, 8);
double x = 0;
int b = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop()
{
  float val = (exp(sin(millis() / 2000.0 * PI)) - 0.36787944) * 108.0;
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, val));
  }
  strip.show();
}


/*

  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();

  if ((i == 1) && (currentMillis - previousMillis >= timerTime))
  {
  i = 0;
  previousMillis = currentMillis;  // Remember the time
  for (int k = 0; k < strip.numPixels(); k++) {
    strip.setPixelColor(k, strip.Color(0, 0, 10));
  }

  strip.show();
  }

  else if ((i == 0) && (currentMillis - previousMillis >= timerTime))
  {
  i = 1;  // turn it on
  previousMillis = currentMillis;   // Remember the time
  for (int k = 0; k < strip.numPixels(); k++) {
    strip.setPixelColor(k, strip.Color(8, 0, 0));
    strip.show();
  }
  }
  }

*/

