#include <FastLED.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <time.h>

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

#define LED_PIN 21
#define NUM_LEDS 60
#define BRIGHTNESS 32
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int ledLookup[60] = {30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31};

CRGB hourColor = CRGB(0, 0, 255);
CRGB minuteColor = CRGB(255, 0, 0);

void setup() {
  WiFiManager wifiManager;
  wifiManager.autoConnect();
  wifiManager.setConfigPortalTimeout(180);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
}

void displayTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return;

  FastLED.clear();
  leds[ledLookup[((timeinfo.tm_hour * 5) + (timeinfo.tm_min / 12)) % 60]] += hourColor;
  leds[ledLookup[timeinfo.tm_min]] += minuteColor;
  Serial.println();
  FastLED.show();
}