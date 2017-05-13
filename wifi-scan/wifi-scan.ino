#include <ESP8266WiFi.h>
bool async = true;
bool hide = true;
int n; // # of nedwerks
#define SCAN_PERIOD 5000 // how long it takes to scan 
long lastScanMillis;

/* This is a sketch to scan for WiFi networks and print them out over the serial port.
   More mischief planned for later.

*/

void setup() {
  Serial.begin(115200);
  pinMode(0,OUTPUT); // the LED thing 
  Serial.println();
  Serial.println("scanning");
  WiFi.mode(WIFI_STA); // we're a station
  WiFi.disconnect(); // but we're gonna roam freeeee
  delay(100);
}

void loop() {
  digitalWrite(0,HIGH); // turn little LED on 
  Serial.println("scanning!!");
  Serial.print(n); 
  Serial.println(" networks found"); 
  n = WiFi.scanNetworks();
  for (int i = 0; i < n; i++)
  {
    Serial.println(WiFi.SSID(i));
  }
  Serial.println();
  digitalWrite(0,LOW); 
  delay(2000);
}
