#include "Font.h"

// Define and initialize the static array
int Font::FontMapper[255];
// Static function to initialize the FontMapper array
void Font::initializeFontMapper() {
    FontMapper['A'] = 0;
    FontMapper['B'] = 1;
    FontMapper['C'] = 2;
    // You can initialize more entries as needed
}

FontProperties Font::fontPropertiesExtracter(const uint8_t letter[16])
{
    int letterHeight = 0;
    int letterWidth = 0;

    uint8_t letterSizeProperties = 0;
    for (int i = 7; i >= 0; i--)
    {
        int lastDigit = letter[i] & 1;
        letterSizeProperties <<= 1;
        letterSizeProperties |= lastDigit;
    }

    for (int i = 0; i < 4; i++)
    {

        int lastBit = 0;
        lastBit = letterSizeProperties & 1;
        letterWidth <<= 1;
        letterWidth |= lastBit;
        letterSizeProperties >>= 1;
        // std::bitset<8> binary(letterWidth);
        // std::cout << binary << std::endl;
    }

    for (int i = 0; i < 4; i++)
    {

        int lastBit = 0;
        lastBit = letterSizeProperties & 1;
        letterHeight <<= 1;
        letterHeight |= lastBit;
        letterSizeProperties >>= 1;
        // std::bitset<8> binary(letterWidth);
        // std::cout << binary << std::endl;
    }

    FontProperties dp;
    dp.width = letterWidth;
    dp.height = letterHeight;
    return dp;
}
