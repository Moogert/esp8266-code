#include <ESP8266WiFi.h>
uint8_t MAC_array[6];
char MAC_char[18];

void setup() {
  pinMode(0, OUTPUT);
  pinMode(12, OUTPUT); // we're going to blink a basic LED on pin 12
  Serial.begin(115200); // is this the offending line??
  // Serial.println("encoding test!!");

  WiFi.macAddress(MAC_array); // need to find MAC address
  for (int i = 0; i < sizeof(MAC_array); ++i) {
    // sprintf(MAC_char,"%s%02x:",MAC_char,MAC_array[i]);
    sprintf(MAC_char, "%s%02x:", MAC_char, MAC_array[i]);
  }

  Serial.println(MAC_char);
}



void loop() {
  digitalWrite(0, HIGH);
  digitalWrite(12, HIGH);
  delay(500); //
  digitalWrite(0, LOW);
  digitalWrite(12, LOW);
  delay(500);
}






