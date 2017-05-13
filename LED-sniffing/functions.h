// This-->tab == "functions.h"
#include <Adafruit_NeoPixel.h>
#include <math.h>
// OK need to define variables here too 
#define PIN 14
uint16_t mod2 = 0;
uint16_t mod1 = 0;
uint16_t i = 0;
float val = 0; 


Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);
// Expose Espressif SDK functionality
extern "C" {
#include "user_interface.h"
  typedef void (*freedom_outside_cb_t)(uint8 status);
  int  wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
  void wifi_unregister_send_pkt_freedom_cb(void);
  int  wifi_send_pkt_freedom(uint8 *buf, int len, bool sys_seq);
}

#include <ESP8266WiFi.h>
#include "./structures.h"
uint32_t purple = strip.Color(4, 0, 8);
#define MAX_APS_TRACKED 100
#define MAX_CLIENTS_TRACKED 200

beaconinfo aps_known[MAX_APS_TRACKED];                    // Array to save MACs of known APs
int aps_known_count = 0;                                  // Number of known APs
int nothing_new = 0;
clientinfo clients_known[MAX_CLIENTS_TRACKED];            // Array to save MACs of known CLIENTs
int clients_known_count = 0;                              // Number of known CLIENTs



int register_beacon(beaconinfo beacon) // we register a new beacom
{
  int known = 0;   // Clear known flag
  for (int u = 0; u < aps_known_count; u++)
  {
    if (! memcmp(aps_known[u].bssid, beacon.bssid, ETH_MAC_LEN)) {
      known = 1;
      break;
    }   // AP known => Set known flag
  }
  if (! known)  // AP is NEW, copy MAC to array and return it
  {
    memcpy(&aps_known[aps_known_count], &beacon, sizeof(beacon));
    aps_known_count++;

    if ((unsigned int) aps_known_count >=
        sizeof (aps_known) / sizeof (aps_known[0]) ) {
      Serial.printf("exceeded max aps_known\n");
      aps_known_count = 0;
    }
  }
  return known;
}


// we register a new client - we want to invoke the LED
// procedure if it's a client of interest to us
int register_client(clientinfo ci)
{
  int known = 0;   // Clear known flag
  for (int u = 0; u < clients_known_count; u++) // if we've seen this before...
  {
    // compare
    if (! memcmp(clients_known[u].station, ci.station, ETH_MAC_LEN)) { // if known
      known = 1;
      break; // break
    }
  }
  if (! known) // if not...
  {
    memcpy(&clients_known[clients_known_count], &ci, sizeof(ci));
    
    /*
    // need to compare to a known list of interesting MACs
    // lfind(ci.bssid, knownMacs, sizeof(knownMacs), sizeof(ci));
    
    */
    
    clients_known_count++;

    if ((unsigned int) clients_known_count >=
        sizeof (clients_known) / sizeof (clients_known[0]) ) { // if we have too many...
      Serial.printf("exceeded max clients_known\n");
      clients_known_count = 0; // ...we go back to the beginning.
    }
  }
  return known;
}

void print_beacon(beaconinfo beacon)
{
  if (beacon.err != 0) {
    //Serial.printf("BEACON ERR: (%d)  ", beacon.err);
  } else {
    Serial.printf("BEACON: <=============== [%32s]  ", beacon.ssid);
    for (int i = 0; i < 6; i++) Serial.printf("%02x", beacon.bssid[i]);
    Serial.printf("   %2d", beacon.channel);
    Serial.printf("   %4d\r\n", beacon.rssi);
  }
}

// This is a function that will light up the neopixels when we find a MAC we want


/*
void lightShow() {
  uint32_t c = strip.Color(4, 0, 8);
  uint32_t off = strip.Color(0, 0, 0); // how to turn everything off
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    mod1 = (i + 2) % 12;
    mod2 = (i + 3) % 12;
    strip.setPixelColor(i, c);
    strip.setPixelColor(mod1, c);
    strip.setPixelColor(mod2, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(i, off);
    strip.setPixelColor(mod1, off);
    strip.setPixelColor(mod2, off);

  }
}
*/

void print_client(clientinfo ci)
{
  int u = 0;
  int known = 0;   // Clear known flag
  if (ci.err != 0) {
    // nothing
  } else {
    Serial.printf("DEVICE: ");
    for (int i = 0; i < 6; i++) Serial.printf("%02x", ci.station[i]);
    Serial.printf(" ==> ");

    for (u = 0; u < aps_known_count; u++)
    {
      if (! memcmp(aps_known[u].bssid, ci.bssid, ETH_MAC_LEN)) {
        Serial.printf("[%32s]", aps_known[u].ssid);
        known = 1;     // AP known => Set known flag
        break;
      }
    }

    if (! known)  {
      Serial.printf("   Unknown/Malformed packet \r\n");
      //  for (int i = 0; i < 6; i++) Serial.printf("%02x", ci.bssid[i]);
    } else {
      Serial.printf("%2s", " ");
      for (int i = 0; i < 6; i++) Serial.printf("%02x", ci.ap[i]);
      Serial.printf("  %3d", aps_known[u].channel);
      Serial.printf("   %4d\r\n", ci.rssi);
    }
  }
}

void promisc_cb(uint8_t *buf, uint16_t len)
{
  int i = 0;
  uint16_t seq_n_new = 0;
  if (len == 12) {
    struct RxControl *sniffer = (struct RxControl*) buf;
  } else if (len == 128) {
    struct sniffer_buf2 *sniffer = (struct sniffer_buf2*) buf;
    struct beaconinfo beacon = parse_beacon(sniffer->buf, 112, sniffer->rx_ctrl.rssi);
    if (register_beacon(beacon) == 0) {
      print_beacon(beacon);
      nothing_new = 0;
    }
  } else {
    struct sniffer_buf *sniffer = (struct sniffer_buf*) buf;
    //Is data or QOS?
    if ((sniffer->buf[0] == 0x08) || (sniffer->buf[0] == 0x88)) {
      struct clientinfo ci = parse_data(sniffer->buf, 36, sniffer->rx_ctrl.rssi, sniffer->rx_ctrl.channel);
      if (memcmp(ci.bssid, ci.station, ETH_MAC_LEN)) {
        if (register_client(ci) == 0) {
          print_client(ci);
          nothing_new = 0;
        }
      }
    }
  }
}

