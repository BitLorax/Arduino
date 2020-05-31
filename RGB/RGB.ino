#include <FastLED.h>
#define NUM_LEDS 24
#define DATA_PIN 9
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  leds[0] = CRGB::Red;
  leds[4] = CRGB::Blue;
  FastLED.show();
  delay(30);
}
