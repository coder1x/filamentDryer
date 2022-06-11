#ifndef Display_H
#define Display_H
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// -- Дисплей ST7735 128х128
#define TFT_WIDTH 128
#define TFT_HEIGHT 128
#define TFT_CS 2
#define TFT_RST 19
#define TFT_DC 5
#define TFT_MOSI 23 // Data out
#define TFT_SCLK 18 // Clock out

class Display
{
public:
  Display();
  void drawText(const char *text, uint16_t color, uint16_t color2, int x, int y, uint8_t size = 1);
  uint16_t colorHex(String color);
  String utf8Rus(String source);
  Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

private:
};

#endif