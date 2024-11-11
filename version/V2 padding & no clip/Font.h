#ifndef FONT_H
#define FONT_H

#include <cstdint>

struct FontProperties
{
    int width;
    int height;
};

class Font
{
public:
    static int FontMapper[255];
    static FontProperties fontPropertiesExtracter(const uint8_t letter[16]);
    // Static constructor-like function to initialize the static array
    static void initializeFontMapper();
};

// A static block to automatically initialize the array
struct FontInitializer
{
    FontInitializer() { Font::initializeFontMapper(); }
};

// Declare a static instance of the initializer to trigger the constructor
static FontInitializer fontInitializer;

#endif // HELPER_H
