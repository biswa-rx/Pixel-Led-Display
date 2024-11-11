#ifndef PIXEL_H
#define PIXEL_H

#include <FastLED.h>

// Define the type for the configuration function pointer
typedef int (*ConfigFunc)(int, int);

class Pixel {
private:
    CRGB *leds;                   // LED array
    int height;                    // Number of rows in the matrix
    int width;                     // Number of columns in the matrix
    ConfigFunc mapper;             // Function pointer for configuration mapping

public:
    // Constructor that accepts a configuration function pointer
    Pixel(CRGB *ledArray, int h, int w, ConfigFunc configFunc);

    // Function to set a pixel color based on (x, y) coordinates
    void glow(int x, int y, CRGB color);

    // Clear the entire LED array
    void clear();

    // Display the LED changes
    void show();
};

#endif // PIXEL_H
