#include "render.h"

#include <bitset>

RGBA **Render::displayBuffer = nullptr;

Render::Render(RGBA **displayBuffer, uint16_t displayWidth, uint16_t displayHeight)
{
    this->displayBuffer = displayBuffer;
    this->displayWidth = displayWidth;
    this->displayHeight = displayHeight;
    this->solidColor = {255, 255, 255, 255};
    this->canvas = {0, 0, displayWidth, displayHeight};
    this->canvasColor = {0, 0, 0, 0};
    this->textProperties.backgroudColor = {0, 0, 0, 0};
    this->textProperties.textColor = {255, 255, 255, 255};
}

Render::Render(RGBA **displayBuffer, uint16_t displayWidth, uint16_t displayHeight, RGBA solidColor, Canvas canvas, RGBA canvasColor)
{
    this->displayBuffer = displayBuffer;
    this->displayWidth = displayWidth;
    this->displayHeight = displayHeight;
    this->solidColor = solidColor;
    this->canvas = canvas;
    this->canvasColor = canvasColor;
    this->textProperties.backgroudColor = canvasColor;
    this->textProperties.textColor = solidColor;
    fillCanvas(canvasColor);
}

void Render::eraseCanvas()
{
    for (int x = canvas.offsetX; x < canvas.canvasMaxX; x++)
    {
        for (int y = canvas.offsetY; y < canvas.canvasMaxY; y++)
        {
            displayBuffer[y][x] = RGBA(0, 0, 0, 0);
        }
    }
}

void Render::fillCanvas(RGBA canvasColor)
{
    for (int x = canvas.offsetX; x <= canvas.canvasMaxX; x++)
    {
        for (int y = canvas.offsetY; y <= canvas.canvasMaxY; y++)
        {
            displayBuffer[y][x] = canvasColor;
        }
    }
    this->canvasColor = canvasColor;
}

int Render::decodeVerticalLine(const uint8_t letter[16], int rowNumber)
{
    int letterHeight = 0;
    int letterWidth = 0;

    FontProperties dp = Font::fontPropertiesExtracter(letter);
    letterWidth = dp.width;
    letterHeight = dp.height;

    // std::cout<<"height"<<(int)letterHeight<<" width"<<letterWidth<<std::endl;

    if (rowNumber >= letterWidth || rowNumber < 0)
    {
        return -1;
    }
    int result = 0;
    int horizontalLine = letter[rowNumber];
    horizontalLine >>= 1;

    return horizontalLine;
}

Coordinate Render::chracterRenderer(const uint8_t* character8BitFont, Coordinate curserPositionCoordinate, RGBA textColor, RGBA backgroundColor)
{
    FontProperties fontProp = Font::fontPropertiesExtracter(character8BitFont);
    int x = 0,y = 0;
    for (x = 0; x < fontProp.width; x++)
    {
        if(curserPositionCoordinate.X + x >= displayWidth || curserPositionCoordinate.X + x > canvas.canvasMaxX || curserPositionCoordinate.X + x < 0 || curserPositionCoordinate.X + x < canvas.offsetX) {
            continue;
        }
        int verticalLine = decodeVerticalLine(character8BitFont, x);

        for (y = 0; y < fontProp.height; y++)
        {
            //For prevent memory out of bound and canvas dead end cross
            if(curserPositionCoordinate.Y + y >= displayHeight || curserPositionCoordinate.Y + y > canvas.canvasMaxY || curserPositionCoordinate.Y + y < 0 || curserPositionCoordinate.Y + y < canvas.offsetY) {
                continue;
            }

            if (verticalLine & 1)
            {
                displayBuffer[curserPositionCoordinate.Y + y][curserPositionCoordinate.X + x] = textColor;
            }
            else
            {
                displayBuffer[curserPositionCoordinate.Y + y][curserPositionCoordinate.X + x] = backgroundColor;
            }

            verticalLine >>= 1;
        }
    }
    
    return Coordinate({curserPositionCoordinate.X + x, curserPositionCoordinate.Y + y});
}

Coordinate Render::textRenderer(const uint8_t font8Bit[][16], const char *text, RGBA textColor, RGBA backgroudColor)
{
    int length = strlen(text);
    char textCopy[length];
    for (int i = 0; i < length; i++)
    {
        textCopy[i] = text[i];
    }
    textProperties.text = textCopy;
    
    char currentLetter;
    Coordinate curserCoordinate = {canvas.offsetX,canvas.offsetY};
    Coordinate curserCoordinateCopy = curserCoordinate;
    for (int i = 0; i < length; i++)
    {
        currentLetter = text[i];

        int letterIndex = Font::FontMapper[currentLetter];
        const uint8_t *characterFont = font8Bit[letterIndex];

        curserCoordinate = chracterRenderer(characterFont, curserCoordinate, textColor, backgroudColor);
        curserCoordinateCopy = curserCoordinate;
        curserCoordinate.Y = canvas.offsetY;
    }
    return curserCoordinateCopy;
}

Coordinate Render::textRenderer(const uint8_t font8Bit[][16], const char *text)
{
    return textRenderer(font8Bit, text, solidColor, canvasColor);
}
