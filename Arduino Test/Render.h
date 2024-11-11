#ifndef RENDER_H
#define RENDER_H

#include "RGBA.h"
#include "Font.h"
#include "Pixel.h"

#ifdef ARDUINO
#include <Arduino.h> // For Serial
#else
#include <bitset>
#include <stdint.h>
#include <iostream> // For std::cout
#include <cstring>
#endif

struct Canvas
{
  int offsetX = 0;
  int offsetY = 0;
  int canvasMaxX = 0;
  int canvasMaxY = 0;
};

struct Coordinate
{
  int X = 0;
  int Y = 0;
};

struct TextProperties
{
  char* text;
  int topPadding = 0;
  int leftPadding = 0;
  int topClip = 0;
  int buttomClip = 0;
  int leftClip = 0;
  int rightClip = 0;
  CRGB textColor;
  CRGB backgroudColor;
};

class Render
{
private:
  Pixel matrix;
  int displayWidth;
  int displayHeight;
  CRGB solidColor;
  Canvas canvas;
  CRGB canvasColor;
  TextProperties textProperties;
public:
  Render();
  Render(Pixel matrix, int displayWidth, int displayHeight);
  Render(Pixel matrix, int displayWidth, int displayHeight, CRGB solidColor, Canvas canvas, CRGB canvasColor);

  void eraseCanvas();
  void fillCanvas(CRGB canvasColor);

  int decodeVerticalLine(const uint8_t letter[16], int rowNumber);
  Coordinate chracterRenderer(const uint8_t* character8BitFont, Coordinate curserPositionCoordinate, CRGB textColor, CRGB backgroundColor);
  Coordinate textRenderer(const uint8_t font8Bit[][16], char *text);
  Coordinate textRenderer(const uint8_t font8Bit[][16], TextProperties textProperties);
  Coordinate refreshCanvas(const uint8_t font8Bit[][16]);

  void setTopPadding(int padding);
  void setLeftPadding(int padding);
};

#endif