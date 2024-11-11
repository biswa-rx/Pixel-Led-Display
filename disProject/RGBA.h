#ifndef RGBA_H
#define RGBA_H

#include <stdint.h>  // For fixed-width types like uint8_t

class RGBA {
private:
    uint8_t r;  // Red component (0-255)
    uint8_t g;  // Green component (0-255)
    uint8_t b;  // Blue component (0-255)
    uint8_t a;  // Alpha (transparency) component (0-255)

public:
    // Constructor with default values
    RGBA(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255);

    // Getter methods
    uint8_t getRed() const;
    uint8_t getGreen() const;
    uint8_t getBlue() const;
    uint8_t getAlpha() const;

    // Setter methods
    void setRed(uint8_t red);
    void setGreen(uint8_t green);
    void setBlue(uint8_t blue);
    void setAlpha(uint8_t alpha);

    // Conditionally compile different print() functions for Arduino and C++
    void print() const;
};

#endif  // RGBA_H
