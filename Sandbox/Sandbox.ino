#include <FastLED.h>
#include <stdlib.h>

#define NUM_LEDS 25
#define DATA_PIN 9
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 25; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();
}
