#include "RGBA.h"

#ifdef ARDUINO
  #include <Arduino.h>  // For Serial
#else
  #include <iostream>   // For std::cout
#endif

// Constructor with default values
RGBA::RGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : r(red), g(green), b(blue), a(alpha) {}

// Getter methods
uint8_t RGBA::getRed() const { return r; }
uint8_t RGBA::getGreen() const { return g; }
uint8_t RGBA::getBlue() const { return b; }
uint8_t RGBA::getAlpha() const { return a; }

// Setter methods
void RGBA::setRed(uint8_t red) { r = red; }
void RGBA::setGreen(uint8_t green) { g = green; }
void RGBA::setBlue(uint8_t blue) { b = blue; }
void RGBA::setAlpha(uint8_t alpha) { a = alpha; }

// Conditionally compile different print() implementations
void RGBA::print() const {
#ifdef ARDUINO
    // Print using Arduino's Serial interface
    Serial.print("RGBA(");
    Serial.print(r);
    Serial.print(", ");
    Serial.print(g);
    Serial.print(", ");
    Serial.print(b);
    Serial.print(", ");
    Serial.print(a);
    Serial.println(")");
#else
    // Print using standard C++ std::cout
    std::cout << "RGBA(" << static_cast<int>(r) << ", " 
              << static_cast<int>(g) << ", " 
              << static_cast<int>(b) << ", " 
              << static_cast<int>(a) << ")\n";
#endif
}
