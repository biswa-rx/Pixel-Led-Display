#include <FastLED.h>

#define LED_PIN     2    // Pin where LED strip is connected
#define NUM_LEDS    1250   // Number of LEDs in the strip
#define DELAY_TIME  0  // Delay time in milliseconds

CRGB leds[NUM_LEDS];     // Define the array of LEDs

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);  // Initialize the LED strip for ESP32
//  FastLED.setBrightness(100);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;  // Set the current LED to red
//    FastLED.show();       // Update the strip to show the color
    delay(DELAY_TIME);    // Wait for the defined delay
  }
  FastLED.show();
  delay(1000);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green;  // Set the current LED to green
//    FastLED.show();         
    delay(DELAY_TIME);     
  }
  FastLED.show();
  delay(1000);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;  // Set the current LED to blue
//    FastLED.show();        
    delay(DELAY_TIME);     
  }
  FastLED.show();
  delay(1000);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Cyan;  // Set the current LED to cyan
//    FastLED.show();        
    delay(DELAY_TIME);     
  }
  FastLED.show();
  delay(1000);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Yellow;  // Set the current LED to yellow
//    FastLED.show();          
    delay(DELAY_TIME);      
  }
  FastLED.show();
  delay(1000);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Magenta;  // Set the current LED to magenta
//    FastLED.show();           
    delay(DELAY_TIME);       
  }
  FastLED.show();
  delay(1000);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;  // Set the current LED to white
//    FastLED.show();         
    delay(DELAY_TIME);     
  }
  FastLED.show();
  delay(1000);
}
