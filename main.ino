#include <FastLED.h>

#define LED_PIN 21
#define NUM_LEDS 60
#define BRIGHTNESS 32
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB setupLeds[NUM_LEDS];
CRGB leds[NUM_LEDS];

void setup()
{
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(setupLeds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS);

    remapLeds(setupLeds, leds);

    leds[59] = CRGB::White;
	leds[14] = CRGB::White;
	leds[29] = CRGB::White;
	leds[44] = CRGB::White;
	FastLED.show();
}

void loop()
{
	
}

void remapLeds(CRGB* setupLeds, CRGB* remapedLeds) {
    for (int i = 0; i < NUM_LEDS; i++)
    {
        int currentLed = (i <= 29) ? (i - 30) : (i + 30);
        leds[i] = setupLeds[currentLed];
    }
    
}