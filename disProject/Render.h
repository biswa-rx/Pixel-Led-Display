#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include "RGBA.h"
#include "Font.h"

#ifdef ARDUINO
#include <Arduino.h> // For Serial
#else
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
  RGBA textColor;
  RGBA backgroudColor;
};

class Render
{
private:
  static RGBA **displayBuffer;
  uint16_t displayWidth;
  uint16_t displayHeight;
  RGBA solidColor;
  Canvas canvas;
  RGBA canvasColor;
  TextProperties textProperties;
public:
  Render(RGBA **displayBuffer, uint16_t displayWidth, uint16_t displayHeight);
  Render(RGBA **displayBuffer, uint16_t displayWidth, uint16_t displayHeight, RGBA solidColor, Canvas canvas, RGBA canvasColor);

  void eraseCanvas();
  void fillCanvas(RGBA canvasColor);

  int decodeVerticalLine(const uint8_t letter[16], int rowNumber);
  Coordinate chracterRenderer(const uint8_t* character8BitFont, Coordinate curserPositionCoordinate, RGBA characterColor, RGBA backgroundColor);
  Coordinate textRenderer(const uint8_t font8Bit[][16], char *text);
  Coordinate textRenderer(const uint8_t font8Bit[][16], TextProperties textProperties);
  Coordinate refreshCanvas(const uint8_t font8Bit[][16]);

  void setTopPadding(int padding);
  void setLeftPadding(int padding);
};

#endif