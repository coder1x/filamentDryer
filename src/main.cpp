#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include <GyverMAX6675.h>
#include "PWMrelay.h"
#include <Wire.h>

#define TFT_WIDTH 128
#define TFT_HEIGHT 128
#define TFT_CS 2
#define TFT_RST 19
#define TFT_DC 5
#define TFT_MOSI 23 // Data out
#define TFT_SCLK 18 // Clock out
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// MAX6675
#define CLK_PIN 4   // Пин SCK
#define DATA_PIN 21 // Пин SO
#define CS_PIN 22   // Пин CS

#define RELAY_PIN 13
PWMrelay relay(RELAY_PIN);

// указываем пины в порядке SCK SO CS
GyverMAX6675<CLK_PIN, DATA_PIN, CS_PIN> sens;

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

// -- таймер
int milliseconds = 0;
int hour = 0;
int minutes = 0;
int seconds = 0;

void temperatureSensor();
void clockDryer(int time);
void drawtext(char *text, uint16_t color, uint16_t color2, int x, int y);

void setup()
{
  Serial.begin(921600);
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(BLACK);

  relay.setPeriod(5000); // установка периода ШИМ в миллисекундах. 1000 соответствует 1 Гц
  relay.setPWM(255);     // установка заполнения шим, 0-255 (соответствует 0-100%)
  relay.setLevel(HIGH);
}

void loop()
{
  int time = 200;
  temperatureSensor();
  clockDryer(time);
  delay(time);

  relay.tick();
}

void temperatureSensor()
{
  char buffer[20] = "";

  if (sens.readTemp())
  { // Читаем температуру

    const int temp = sens.getTempInt();

    sprintf(buffer, "%s%d%s", " Temperature: ", temp, " C");
    drawtext(
        buffer,
        MAGENTA,
        BLACK,
        0,
        5);

    if (temp < 30)
    {
      relay.setPWM(20);
    }
    else
    {
      relay.setPWM(255);
    }
  }
  else
  {
    drawtext(
        " Error Temp",
        MAGENTA,
        BLACK,
        0,
        5);
  }

  tft.drawLine(0, 15, 128, 15, YELLOW);
}

void clockDryer(int time)
{
  char buffer[20] = "";
  milliseconds += time;

  if (milliseconds < 1000)
    return;

  seconds += milliseconds / 1000;
  milliseconds = 0;

  if (seconds == 60)
  {
    seconds = 0;
    ++minutes;

    if (minutes == 60)
    {
      minutes = 0;
      ++hour;
    }
  }

  sprintf(
      buffer,
      "%s%d%s%d%s%d",
      " Time: ",
      hour,
      " : ",
      minutes,
      " : ",
      seconds);
  drawtext(
      buffer,
      MAGENTA,
      BLACK,
      0,
      25);
}

void drawtext(
    char *text,
    uint16_t color,
    uint16_t color2,
    int x,
    int y)
{
  tft.setCursor(x, y);
  tft.setTextColor(color, color2);
  tft.setTextWrap(true);
  tft.print(text);
}
