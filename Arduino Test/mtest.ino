#include <FastLED.h>
#include "Pixel.h"
#include "Render.h"

#define DATA_PIN 2
#define HEIGHT 8          // 8 rows
#define WIDTH 25          // 25 columns
#define NUM_LEDS (HEIGHT * WIDTH)

CRGB leds[NUM_LEDS];

const uint8_t smallLetterFont_8[3][16] = {
    {0, 253, 39, 39, 254, 253, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // A

    {1, 254, 254, 146, 146, 255, 109, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // B

    {1, 56, 124, 198, 130, 131, 131, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // C

};

// Function for "S" configuration (alternate rows left-to-right and right-to-left)
int SConfig(int x, int y) {
    return (y % 2 == 0) ? (y * WIDTH + x) : (y * WIDTH + (WIDTH - 1 - x));
}

// Lambda for "Z" configuration (all rows left-to-right)
auto ZConfig = [](int x, int y) -> int {
    return y * WIDTH + x;
};

// Initialize Pixel object with the "S" configuration
Pixel matrix(leds, HEIGHT, WIDTH, SConfig);
Render rd(matrix,WIDTH,HEIGHT);

void setup() {
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    matrix.setBrightness(128);    // Set initial brightness
    matrix.clear();               // Clear all LEDs
    Serial.begin(115200); // Initialize serial communication for printing

    rd.textRenderer(smallLetterFont_8,"ABC");

    matrix.printBuffer();
}

void loop() {
   
}
