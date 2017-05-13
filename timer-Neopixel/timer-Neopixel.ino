//
// ESP8266 Timer Example
// SwitchDoc Labs  October 2015
// A copy is available at:
// http://www.switchdoc.com/2015/10/iot-esp8266-timer-tutorial-arduino-ide/


extern "C" {
#include "user_interface.h"
}

os_timer_t myTimer;

bool tickOccured;

// start of timerCallback
void timerCallback(void *pArg) {

  // add LED stuff
  // tickOccured = true;
  val = (exp(sin(x * PI)) - 0.36787944) * 108.0; // this ranges 0 - 255
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, val));
  }
  strip.show();
  x += 
}


} // End of timerCallback

void user_init(void) {
  /*
    os_timer_setfn - Define a function to be called when the timer fires

    void os_timer_setfn(
       os_timer_t *pTimer,
       os_timer_func_t *pFunction,
       void *pArg)

    Define the callback functi1on that will be called when the timer reaches zero. The pTimer parameters is a pointer to the timer control structure.

    The pFunction parameters is a pointer to the callback function.

    The pArg parameter is a value that will be passed into the called back function. The callback function should have the signature:
    void (*functionName)(void *pArg)

    The pArg parameter is the value registered with the callback function.
  */

  os_timer_setfn(&myTimer, timerCallback, NULL);

  /*
        os_timer_arm -  Enable a millisecond granularity timer.

    void os_timer_arm(
        os_timer_t *pTimer,
        uint32_t milliseconds,
        bool repeat)

    Arm a timer such that is starts ticking and fires when the clock reaches zero.

    The pTimer parameter is a pointed to a timer control structure.
    The milliseconds parameter is the duration of the timer measured in milliseconds. The repeat parameter is whether or not the timer will restart once it has reached zero.

  */

  os_timer_arm(&myTimer, 1000, true); // timer runs every second
} // End of user_init


void setup() {


  Serial.begin(115200);
  Serial.println();
  Serial.println();



  Serial.println("");
  Serial.println("--------------------------");
  Serial.println("ESP8266 Timer Test");
  Serial.println("--------------------------");
  tickOccured = false;
  user_init();

}

void loop() {

  if (tickOccured == true)
  {

    Serial.println("Tick Occurred");
    tickOccured = false;

  }

  yield();  // or delay(0);

}





