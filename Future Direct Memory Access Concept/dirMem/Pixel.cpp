#include "Pixel.h"

// Constructor that accepts a configuration function pointer
Pixel::Pixel(CRGB *ledArray, int h, int w, ConfigFunc configFunc)
    : leds(ledArray), height(h), width(w), mapper(configFunc) {}

// Function to set a pixel color based on (x, y) coordinates
void Pixel::glow(int x, int y, CRGB color) {
    int index = mapper(x, y);         // Use the mapping function to find the correct index
    if (index >= 0 && index < height * width) {
        leds[index] = color;          // Set color at calculated index
    }
}

// Clear the entire LED array
void Pixel::clear() {
    fill_solid(leds, height * width, CRGB::Black);
}

// Display the LED changes
void Pixel::show() {
    FastLED.show();
}
