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
    int numLeds;                   // Total number of LEDs
    ConfigFunc mapper;             // Function pointer for configuration mapping
    uint8_t brightness;            // Store brightness value

public:

    // Constructor that accepts a configuration function pointer
    Pixel(CRGB *ledArray, int h, int w, ConfigFunc configFunc);

    // Set the overall brightness level
    void setBrightness(uint8_t brightness);

    // Set a pixel color based on (x, y) coordinates
    void setColor(int x, int y, CRGB color);

    // Get the color of a specific pixel
    CRGB getColor(int x, int y);

    // Get individual RGB components of a pixel
    uint8_t getR(int x, int y);
    uint8_t getG(int x, int y);
    uint8_t getB(int x, int y);

    // Clear the entire LED array
    void clear();

    // Fill the entire matrix with a specified color
    void fillSolid(CRGB color);

    // Display the LED changes
    void show();

    // Fade each LED towards black by a specified amount
    void fadeToBlackBy(uint8_t fadeValue);

    // Add a sparkle effect with random LEDs lighting up in a specified color
    void addGlitter(uint8_t chanceOfGlitter, CRGB glitterColor);

    // Scale down the brightness of a specific color
    void scaleColor(int x, int y, uint8_t scale);

    // Blend smoothly between two colors for a specified pixel
    void blendColor(int x, int y, CRGB targetColor, uint8_t blendAmount);

    // Function to print the current state of the LED matrix to the serial monitor
    void printBuffer();

};

#endif // PIXEL_H
