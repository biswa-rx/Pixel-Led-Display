#include <FastLED.h>

#define LED_PIN 5
#define NUM_LEDS 400

CRGB leds[NUM_LEDS];

const uint8_t letter[10][8] = {
    {0b01111110,
     0b11000011,
     0b11000111,
     0b11001111,
     0b11011111,
     0b11110111,
     0b11100011,
     0b01111110},

    {0b00011000,
     0b00111000,
     0b01111000,
     0b00011000,
     0b00011000,
     0b00011000,
     0b00011000,
     0b00111110},

    {0b01111110,
     0b11000011,
     0b00000111,
     0b00001110,
     0b00011100,
     0b00111000,
     0b01110000,
     0b11111111},

    {0b01111110,
     0b11000011,
     0b00000111,
     0b00011110,
     0b00000111,
     0b11000011,
     0b11000011,
     0b01111110},

    {0b00001110,
     0b00011110,
     0b00111110,
     0b01101110,
     0b11001110,
     0b11111111,
     0b00001110,
     0b00001110},

    {0b11111111,
     0b11000000,
     0b11000000,
     0b11111110,
     0b00000011,
     0b00000011,
     0b11000011,
     0b01111110},

    {0b00111110,
     0b01100000,
     0b11000000,
     0b11111100,
     0b11000011,
     0b11000011,
     0b01100011,
     0b00111110},

    {0b11111111,
     0b11000011,
     0b00000110,
     0b00001100,
     0b00011000,
     0b00110000,
     0b01100000,
     0b01100000},

    {0b01111110,
     0b11000011,
     0b11000011,
     0b01111110,
     0b11000011,
     0b11000011,
     0b11000011,
     0b01111110},

    {0b01111110,
     0b11000011,
     0b11000011,
     0b01111111,
     0b00000011,
     0b00000011,
     0b11000110,
     0b01111100}
     };

const int size = 25;
uint8_t *renderBuffer = new uint8_t[size];

void clearBuffer()
{
    for (int i = 0; i < 25; i++)
    {
        renderBuffer[i] = 0;
    }
}

void setup()
{
    clearBuffer();
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    // delete[] renderBuffer;
    // pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(250000);
    FastLED.setBrightness(100);
}

uint8_t decodeVerticalLine(const uint8_t letter[], int colNumber)
{
    uint8_t result = 0;
    for (int i = 0; i < 8; i++)
    {
        uint8_t byte = letter[i];
        result <<= 1;
        if (byte & (1 << colNumber))
        {
            result |= 1;
        }
    }
    return result;
}

void addSeparater()
{
    for (int i = 1; i <= 24; i++)
    {
        renderBuffer[i - 1] = renderBuffer[i];
    }
    renderBuffer[24] = 0;
    for (int i = 1; i <= 24; i++)
    {
        renderBuffer[i - 1] = renderBuffer[i];
    }
    renderBuffer[24] = 0;
}

void printLED()
{
    for (int col = 7; col >= 0; col--)
    {

        if (col % 2 == 1)
        {
            for (int row = 0; row < 25; row++)
            {
                uint8_t byte = renderBuffer[row];
                if (byte & (1 << col))
                {
                    leds[(7 - col) * 25 + row] = CRGB(0, 0, 255);
                }
                else
                {
                    leds[(7 - col) * 25 + row] = CRGB(0, 0, 0);
                }
            }
        }
        else
        {
            for (int row = 0; row < 25; row++)
            {
                uint8_t byte = renderBuffer[24 - row];
                if (byte & (1 << col))
                {
                    leds[(7 - col) * 25 + row] = CRGB(0, 0, 255);
                }
                else
                {
                    leds[(7 - col) * 25 + row] = CRGB(0, 0, 0);
                }
            }
        }
    }
    FastLED.show();
    // delay(100);
}

void printBuffer()
{

    for (int col = 7; col >= 0; col--)
    {
        for (int row = 0; row < 25; row++)
        {
            uint8_t byte = renderBuffer[row];
            if (byte & (1 << col))
            {
                // leds[col*50+row] = CRGB(255, 0, 0);
                Serial.print("@ ");
            }
            else
            {
                // leds[col*50+row] = CRGB(0, 255, 0);
                Serial.print("  ");
            }
        }
        Serial.println();
    }
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();

    FastLED.show();
    delay(100);
}

int reverse(int num) {
    int reversed = 0;
    while (num != 0) {
        int digit = num % 10;      // Extract the last digit
        reversed = reversed * 10 + digit;  // Append the digit to reversed number
        num = num / 10;            // Remove the last digit from num
    }
    return reversed;
}


int x = 1;
void loop()
{

    int temp = reverse(x);

    while (temp)
    {
        int digit = temp % 10;
        temp /= 10;
        for (int i = 7; i >=0; i--)
        {
            uint8_t vLine = decodeVerticalLine(letter[digit], i);

            for (int i = 1; i <= 24; i++)
            {
                renderBuffer[i - 1] = renderBuffer[i];
            }
            renderBuffer[24] = vLine;
            // printBuffer(); // it is just printing purpose, not for actual impl.
            printLED();
        }
        addSeparater();

        // printLED();
        // printBuffer();
    }

    delay(1000);
    // fill_solid(leds, NUM_LEDS, CRGB::Black);
    x++;
    // printBuffer();
    clearBuffer();

    addSeparater();
    addSeparater();
}