#include "Pixel.h"

// Constructor that accepts a configuration function pointer
Pixel::Pixel(CRGB *ledArray, int h, int w, ConfigFunc configFunc)
    : leds(ledArray), height(h), width(w), numLeds(h * w), mapper(configFunc), brightness(255) {
    FastLED.setBrightness(255);   // Set initial brightness
}

// Sets the overall brightness level for the matrix
void Pixel::setBrightness(uint8_t brightness) {
    this->brightness = brightness;
    FastLED.setBrightness(brightness);
}

// Sets a specific pixel's color based on (x, y) coordinates
void Pixel::setColor(int x, int y, CRGB color) {
    int index = mapper(x, y);
    if (index >= 0 && index < numLeds) {
        leds[index] = color;
    }
}

// Gets the color of a specific pixel at (x, y)
CRGB Pixel::getColor(int x, int y) {
    int index = mapper(x, y);
    if (index >= 0 && index < numLeds) {
        return leds[index];
    }
    return CRGB::Black;
}

// Gets the red component of a pixel at (x, y)
uint8_t Pixel::getR(int x, int y) {
    return getColor(x, y).r;
}

// Gets the green component of a pixel at (x, y)
uint8_t Pixel::getG(int x, int y) {
    return getColor(x, y).g;
}

// Gets the blue component of a pixel at (x, y)
uint8_t Pixel::getB(int x, int y) {
    return getColor(x, y).b;
}

// Clears all LEDs to black
void Pixel::clear() {
    fill_solid(leds, numLeds, CRGB::Black);
    FastLED.show();
}

// Fills the entire matrix with a specified color
void Pixel::fillSolid(CRGB color) {
    fill_solid(leds, numLeds, color);
    FastLED.show();
}

// Updates the LEDs with current buffer data
void Pixel::show() {
    FastLED.show();
}

// Fades each LED towards black by a specified amount
void Pixel::fadeToBlackBy(uint8_t fadeValue) {
    fadeToBlackBy(fadeValue);
}

// Adds random sparkles in specified color with a given probability
void Pixel::addGlitter(uint8_t chanceOfGlitter, CRGB glitterColor) {
    if (random8() < chanceOfGlitter) {
        int pos = random16(numLeds);
        leds[pos] = glitterColor;
    }
}

// Scales down the brightness of a specific pixel at (x, y) by a given factor
void Pixel::scaleColor(int x, int y, uint8_t scale) {
    int index = mapper(x, y);
    if (index >= 0 && index < numLeds) {
        leds[index].nscale8(scale);
    }
}

// Smoothly transitions the color of a pixel at (x, y) towards a target color
void Pixel::blendColor(int x, int y, CRGB targetColor, uint8_t blendAmount) {
    int index = mapper(x, y);
    if (index >= 0 && index < numLeds) {
        leds[index] = blend(leds[index], targetColor, blendAmount);
    }
}


// Function to print the current state of the LED matrix to the serial monitor
void Pixel::printBuffer() {
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // New line for the next row
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = mapper(x, y); // Get the corresponding index
            CRGB color = leds[index];  // Get the color at that index

            // Scale down each color component from 255 to 8
            uint8_t scaledR = map(color.red, 0, 255, 0, 8);
            uint8_t scaledG = map(color.green, 0, 255, 0, 8);
            uint8_t scaledB = map(color.blue, 0, 255, 0, 8);

            // Print the scaled color values or '_' if color is black
            if (color == CRGB::Black) {
                Serial.print("_"); // Print underscore if no color
                Serial.print("_"); // Print underscore if no color
                Serial.print("_"); // Print underscore if no color
            } else {
                Serial.print(scaledG); // Print scaled green component
//                Serial.print(" ");
                Serial.print(scaledR); // Print scaled red component
//                Serial.print(" ");
                Serial.print(scaledB); // Print scaled blue component
//                Serial.print(" ");
            }

//            Serial.print(" ");
        }
        Serial.println();
    }
    
}
