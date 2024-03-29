#include "Display.h"
using namespace std;

Display::Display()
{
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(colorHex("#000000"));
  tft.cp437(true);
}

void Display::cursor(
    uint8_t coordsX,
    String color,
    String colorBackground,
    uint16_t x)
{
  drawText(
      "*",
      color,
      colorBackground,
      coordsX,
      x,
      1);
}

uint16_t Display::colorHex(String color)
{
  color.trim();
  color.replace("#", "");
  char charbuf[8];
  color.toCharArray(charbuf, 8);
  long int rgb = stol(charbuf, 0, 16);
  byte r = (byte)(rgb >> 16);
  byte g = (byte)(rgb >> 8);
  byte b = (byte)(rgb);

  return tft.color565(r, g, b);
}

void Display::drawText(
    const char *text,
    String color,
    String color2,
    uint16_t x,
    uint16_t y,
    uint8_t size)
{

  tft.setCursor(x, y);
  tft.setTextColor(
      colorHex(color),
      colorHex(color2));
  tft.setTextWrap(true);
  tft.setTextSize(size);
  tft.print(text);
}

String Display::utf8Rus(String source)
{
  uint16_t i, k;
  String target;
  unsigned char n;
  char m[2] = {'0', '\0'};

  k = source.length();
  i = 0;

  while (i < k)
  {
    n = source[i];
    i++;

    if (n >= 0xC0)
    {
      switch (n)
      {
      case 0xD0:
      {
        n = source[i];
        i++;
        if (n == 0x81)
        {
          n = 0xA8;
          break;
        }
        if (n >= 0x90 && n <= 0xBF)
          n = n + 0x30;
        break;
      }
      case 0xD1:
      {
        n = source[i];
        i++;
        if (n == 0x91)
        {
          n = 0xB8;
          break;
        }
        if (n >= 0x80 && n <= 0x8F)
          n = n + 0x70;
        break;
      }
      }
    }
    m[0] = n;
    target = target + String(m);
  }
  return target;
}