#include <FastLED.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

#define LED_PIN 21
#define NUM_LEDS 60
#define BRIGHTNESS 32
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup()
{
    WiFiManager wifiManager;
    wifiManager.autoConnect();
    wifiManager.setConfigPortalTimeout(180);

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
	
}

void remapLeds(CRGB* leds) {
    CRGB tempLeds[NUM_LEDS];
    for (int i = 0; i < NUM_LEDS; i++)
    {
        int currentLed = (i <= 29) ? (i - 30) : (i + 30);
        tempLeds[i] = leds[currentLed];
    }
    leds = tempLeds;
}