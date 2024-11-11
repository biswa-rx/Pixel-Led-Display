#include <FastLED.h>

#define LED_PIN     2
#define NUM_LEDS    200
#define DELAY_MS    30 // Delay between color changes in milliseconds
#define BRIGHTNESS  255 // 10% brightness

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // Rainbow pattern
  for (int i = 0; i < 50; i++) {
    leds[i] = CHSV((millis() / 10 + i * 5) % 255, 255, 255);
    leds[25+(24-i)] = CHSV((millis() / 10 + i * 5) % 255, 255, 255);
    leds[50+i] = CHSV((millis() / 10 + i * 5) % 255, 255, 255);
    leds[75+(24-i)] = CHSV((millis() / 10 + i * 5) % 255, 255, 255);
    leds[100+i] = CHSV((millis() / 10 + i * 5) % 255, 255, 255);
    leds[125+(24-i)] = CHSV((millis() / 10 + i * 5) % 255, 255, 255);
    leds[150+i] = CHSV((millis() / 10 + i * 5) % 255, 255, 255);
    leds[175+(24-i)] = CHSV((millis() / 10 + i * 5) % 255, 255, 255);
  }
  
  // Show the updated LED colors
  FastLED.show();
  
  // Delay for a short period
  delay(DELAY_MS);
}
