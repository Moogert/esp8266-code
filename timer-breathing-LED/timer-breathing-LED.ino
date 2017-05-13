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
double timerTime = 500; // 50ms
float val = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);
uint32_t purple = strip.Color(4, 0, 8);
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;
double x = 0;
int b = 0;
os_timer_t myTimer; // OS defined, soft real-time

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  OCR0A = 0xAF; // when the timer passes 0xAF, INTERRUPT
  TIMSK0 |= _BV(OCIE0A);
}

/*
 *  one cycle every two seconds 
 *  --> x goes from 0 to two every 2 seconds 
 * ---> x goes from 0 to 1 every second 
 * ---> ...in 10ms incremements (bc why not) 
 * ---> 1/100 = 0.01
 * 
 */

SIGNAL(TIMER0_COMPA_vect) // when timer expires
{
  val = (exp(sin(x * PI)) - 0.36787944) * 108.0; // this ranges 0 - 255
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, val));
  }
  strip.show();
  x = x + 0.1; 
}


void loop()
{
  // empty!!!
}




