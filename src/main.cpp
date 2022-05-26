#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <GyverMAX6675.h>
#include "PWMrelay.h"
#include <Wire.h>
using namespace std;

// -- Дисплей ST7735 128х128
#define TFT_WIDTH 128
#define TFT_HEIGHT 128
#define TFT_CS 2
#define TFT_RST 19
#define TFT_DC 5
#define TFT_MOSI 23 // Data out
#define TFT_SCLK 18 // Clock out

// -- термодатчик MAX6675
#define CLK_PIN 4   // Пин SCK
#define DATA_PIN 21 // Пин SO
#define CS_PIN 22   // Пин CS

// -- кнопки
const int buttonLeft = 27;
const int buttonRight = 12;
const int buttonSelect = 14;
const int buttonEnter = 26;

// -- Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

// -- Реле
#define RELAY_PIN 13

// -- подключаем: Дисплей, Реле, Датчик температуры
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
PWMrelay relay(RELAY_PIN);
GyverMAX6675<CLK_PIN, DATA_PIN, CS_PIN> sens; // указываем пины в порядке SCK SO CS

// -- таймер
int hour = 0;
int minutes = 0;
int seconds = 0;

// -- статус кнопки
int buttonState = 0;
bool flag = false;
uint32_t btnTimer = 0;

// -- Объявление функций
void temperatureSensor();
void clockDryer();
void drawtext(char *text, uint16_t color, uint16_t color2, int x, int y);
void buttonClick(int buttonPin);

void setup()
{
  Serial.begin(921600);
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(BLACK);

  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonEnter, INPUT_PULLUP);

  relay.setPeriod(100); // установка периода ШИМ в миллисекундах. 1000 соответствует 1 Гц
  relay.setPWM(255);    // установка заполнения шим, 0-255 (соответствует 0-100%)
  relay.setLevel(LOW);  // по умолчанию выключаем что бы потом быстро включать.
}

void loop()
{

  buttonClick(buttonLeft);
  buttonClick(buttonRight);
  buttonClick(buttonSelect);
  buttonClick(buttonEnter);

  temperatureSensor();
  clockDryer();

  relay.tick();
}

void buttonClick(int buttonPin)
{
  char buffer[20] = "";

  bool btnState = !digitalRead(buttonPin);
  if (btnState && !flag && millis() - btnTimer > 10)
  {
    flag = true;
    btnTimer = millis();

    sprintf(buffer, "%s%d", " press: ", buttonPin);
    drawtext(
        buffer,
        MAGENTA,
        BLACK,
        0,
        35);
  }

  if (!btnState && flag && millis() - btnTimer > 10)
  {
    flag = false;
    btnTimer = millis();

    sprintf(buffer, "%s%d", " release: ", buttonPin);
    drawtext(
        buffer,
        MAGENTA,
        BLACK,
        0,
        45);
  }
}

void temperatureSensor()
{

  static uint32_t timerTemperature = millis();
  if (millis() - timerTemperature < 1000)
    return;
  timerTemperature = millis();

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
      relay.setPWM(50);
    }
    else
    {
      relay.setPWM(255);
    }
  }
  else
  {
    sprintf(buffer, "%s", " Error Temp ");
    drawtext(
        buffer,
        MAGENTA,
        BLACK,
        0,
        5);
  }

  tft.drawLine(0, 15, 128, 15, YELLOW);
}

void clockDryer()
{
  static uint32_t clockTime = millis();
  if (millis() - clockTime < 1000)
    return;
  clockTime = millis();
  char buffer[20] = "";

  ++seconds;
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
