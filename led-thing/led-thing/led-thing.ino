
#include <ESP8266WiFi.h>
void animSetup(void);
void animConfig(uint16_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
void waitForFrame(void);
void renderFrame(void);



const char* ssid     = "adafruit";
const char* password = "ffffffff";
int8_t utc_offset = -5; // hours off of UTC, e.g. EST is -5 
const char* location = "boston%2C%20ma";

const char* path_prefix = "/v1/public/yql?q=select%20item.condition.code%2C%20item.condition.text%20%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22";
const char* path_postfix = "%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";
const char* host = "query.yahooapis.com";
const int httpPort = 80;


int16_t weathercode = -1;
int16_t createhour, createmin;

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  animConfig(0, 0, 0, 0, 0, 0);
  animSetup();
}

uint32_t timekeep=0xFFFF;

void loop() {
  uint32_t currTime = millis();
  // every 30 seconds (or if there's a rollover/first time running, update the weather!
  if ((timekeep > currTime)  || (currTime > (timekeep + 30000))) {
    timekeep = currTime;
    updateWeather();
  }

  waitForFrame();
  renderFrame();

}


