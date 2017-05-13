#include <ESP8266WiFi.h>
bool async = true;
bool net = true;
int n; // # of nedwerks
#define SCAN_PERIOD 5000 // how long it takes to scan 
long lastScanMillis;
String bssid;
String ssid;
uint8_t encryptionType;
int32_t RSSI;
uint8_t* BSSID; //
int32_t channel;
bool isHidden;


/* This is a sketch to scan for WiFi networks and print them out over the serial port.
   More mischief planned for later.

*/

void setup() {
  Serial.begin(115200);
  pinMode(0, OUTPUT); // the LED thing
  Serial.println();
  Serial.println("scanning");
  WiFi.mode(WIFI_STA); // we're a station
  WiFi.disconnect(); // but we're gonna roam freeeee
  delay(100);
}

void loop() {
  long currentMillis = millis();

  if (currentMillis - lastScanMillis > SCAN_PERIOD) { // triggers new scan
    WiFi.scanNetworks(true);
    Serial.println("\nStart the scan");
    lastScanMillis = currentMillis;

  }

  // if we have some networks

  n = WiFi.scanComplete();
  if (n >= 0) {

    for (int i = 0; i < n; i++)
    {
      bssid = WiFi.BSSIDstr(i);
      WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
      Serial.printf("%d: %s, Ch:%d (%ddBm) %s BSSID: %s", i + 1, ssid.c_str(), channel, RSSI, encryptionType == ENC_TYPE_NONE ? "open" : "", isHidden ? "hidden" : "");
      Serial.println(bssid);
    }

  }
}
