#include "render.h"



Render::Render(Pixel matrix, int displayWidth, int displayHeight)
{
    this->matrix = matrix;
    this->displayWidth = displayWidth;
    this->displayHeight = displayHeight;
    this->solidColor = CRGB::White;
    this->canvas.offsetX = 0;
    this->canvas.offsetY = 0;
    this->canvas.canvasMaxX = displayWidth;
    this->canvas.canvasMaxY = displayHeight;
    // this->canvas = {0, 0, displayWidth, displayHeight};
    this->canvasColor = CRGB::Black;
    this->textProperties.backgroudColor = CRGB::Black;
    this->textProperties.textColor = CRGB::White;
}

Render::Render(Pixel matrix, int displayWidth, int displayHeight, CRGB solidColor, Canvas canvas, CRGB canvasColor)
{
    this->matrix = matrix;
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
    matrix.fillSolid(CRGB::Black);
    matrix.show();
}

void Render::fillCanvas(CRGB canvasColor)
{
    matrix.fillSolid(canvasColor);
    matrix.show();
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

Coordinate Render::chracterRenderer(const uint8_t* character8BitFont, Coordinate curserPositionCoordinate, CRGB textColor, CRGB backgroundColor)
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
                // displayBuffer[curserPositionCoordinate.Y + y][curserPositionCoordinate.X + x] = textColor;
                matrix.setColor(curserPositionCoordinate.X + x,curserPositionCoordinate.Y + y,textColor);
            }
            else
            {
                matrix.setColor(curserPositionCoordinate.X + x,curserPositionCoordinate.Y + y,backgroundColor);
            }

            verticalLine >>= 1;
        }
    }

    Coordinate endPosition;
    endPosition.X = curserPositionCoordinate.X + x;
    endPosition.Y = curserPositionCoordinate.Y + y;
    
    return endPosition;
}

Coordinate Render::textRenderer(const uint8_t font8Bit[][16], TextProperties textProperties)
{
    char* text = textProperties.text;
    int length = strlen(text);
    
    char currentLetter;
    // Coordinate curserCoordinate = {canvas.offsetX,canvas.offsetY};
    Coordinate curserCoordinate;
    curserCoordinate.X = canvas.offsetX;
    curserCoordinate.Y = canvas.offsetY;
    Coordinate curserCoordinateCopy = curserCoordinate;
    curserCoordinate.X += textProperties.leftPadding;
    curserCoordinate.Y += textProperties.topPadding;
    for (int i = 0; i < length; i++)
    {
        currentLetter = text[i];

        int letterIndex = Font::FontMapper[currentLetter];
        const uint8_t *characterFont = font8Bit[letterIndex];

        curserCoordinate = chracterRenderer(characterFont, curserCoordinate, textProperties.textColor, textProperties.backgroudColor);
        curserCoordinateCopy = curserCoordinate;
        curserCoordinate.Y = canvas.offsetY + textProperties.topPadding;
    }
    return curserCoordinateCopy;
}

Coordinate Render::textRenderer(const uint8_t font8Bit[][16], char *text)
{
    textProperties.text = text;
    // textProperties.topPadding = 1;
    // textProperties.leftPadding = 1;
    return textRenderer(font8Bit, textProperties);
}

Coordinate Render::refreshCanvas(const uint8_t font8Bit[][16]) {
    eraseCanvas();
    return textRenderer(font8Bit,textProperties);
}

void Render::setTopPadding(int padding)
{
    textProperties.topPadding = padding;
}

void Render::setLeftPadding(int padding)
{
    textProperties.leftPadding = padding;
}
