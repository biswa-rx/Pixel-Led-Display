#include <FastLED.h>
#include "Pixel.h"

#define DATA_PIN 2
#define HEIGHT 8         // 8 rows
#define WIDTH 25         // 25 columns
#define NUM_LEDS (HEIGHT * WIDTH)

CRGB leds[NUM_LEDS];

// Function for "Z" configuration (all rows left-to-right)
int ZConfig(int x, int y) {
    return y * WIDTH + x;
}

// Function for "S" configuration (alternate rows left-to-right and right-to-left)
int SConfig(int x, int y) {
    return (y % 2 == 0) ? (y * WIDTH + x) : (y * WIDTH + (WIDTH - 1 - x));
}

// Initialize Pixel object with the "S" configuration
Pixel matrix(leds, HEIGHT, WIDTH, ZConfig);

void setup() {
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
}

void loop() {
    matrix.clear();                 // Clear the LED matrix

    // Example of moving glow
    static int x = 0, y = 0;
    matrix.glow(x, y, CRGB::Red);   // Light up (x, y) in red
    matrix.show();                  // Update LEDs
    delay(100);

    // Move (x, y) coordinates
    x = (x + 1) % WIDTH;
    if (x == 0) y = (y + 1) % HEIGHT;
}
