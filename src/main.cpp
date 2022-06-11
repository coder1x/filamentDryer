#include "main.h"

void clearLine(int y);

void setup()
{
  Serial.begin(921600);
  attachInterrupt(digitalPinToInterrupt(KEY_SELECT), handleButtonSelect, FALLING);
  attachInterrupt(digitalPinToInterrupt(KEY_ENTER), handleButtonEnter, FALLING);
  attachInterrupt(digitalPinToInterrupt(KEY_LEFT), handleButtonLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(KEY_RIGHT), handleButtonRight, FALLING);
}

void loop()
{
  if (buttonSelect.click())
  {
    ++selectItem;
  }

  showHeader();
  showTimer(selectItem);
  showTemperature(selectItem);
  showFootor(selectItem);
}

void IRAM_ATTR handleButtonLeft()
{
}

void IRAM_ATTR handleButtonRight()
{
}

void IRAM_ATTR handleButtonEnter()
{
}

void IRAM_ATTR handleButtonSelect()
{
  if (buttonSelect.click())
    ++selectItem;

  if (selectItem > 3)
    selectItem = 0;
}

void showHeader()
{
  int temperature = sensor.getTemperature();
  if (temperature != 0)
  {
    char buffer[20];
    sprintf(buffer, "%s%d%s", display.utf8Rus("температура: "), temperature, " C");
    display.drawText(
        buffer,
        COLOR_TEXT,
        COLOR_HIGHLIGHTED,
        0,
        2);
    display.tft.drawLine(
        0,
        12,
        128,
        12,
        display.colorHex(COLOR_LINE));
  }
}

void showTimer(int select)
{
  // hour;
  // minutes;
  // seconds;

  String hourText = String(hour);
  String minutesText = String(minutes);
  String secondsText = String(seconds);

  if (hourText.length() < 2)
    hourText += "0";
  if (minutesText.length() < 2)
    minutesText += "0";
  if (secondsText.length() < 2)
    secondsText += "0";

  String text = hourText + ":" + minutesText + ":" + secondsText;
  String colorText = "";
  int coordsX = 5;
  if (selectItem == 1)
  {
    text = "[" + text + "]";
    colorText = COLOR_FOCUS;
  }
  else
  {
    text = " " + text + " ";
    colorText = COLOR_TEXT;
  }

  char buffer[30];
  sprintf(buffer, "%s", text);
  display.drawText(
      buffer,
      colorText,
      COLOR_HIGHLIGHTED,
      coordsX,
      25,
      2);
  display.tft.drawLine(
      0,
      43,
      128,
      43,
      display.colorHex(COLOR_LINE));
}

void showTemperature(int select)
{
  // maxTemperature

  String temperatureText = String(maxTemperature);

  if (temperatureText.length() < 2)
    temperatureText += "0";

  String text = "MAX T:" + temperatureText;
  String colorText = "";
  int coordsX = 4;
  if (selectItem == 2)
  {
    colorText = COLOR_FOCUS;
    text = "[" + text + "]";
  }
  else
  {
    colorText = COLOR_TEXT;
    text = " " + text + " ";
  }

  char buffer[20];
  sprintf(buffer, "%s", text);
  display.drawText(
      buffer,
      colorText,
      COLOR_HIGHLIGHTED,
      coordsX,
      55,
      2);
  display.tft.drawLine(
      0,
      72,
      128,
      72,
      display.colorHex(COLOR_LINE));
}

void showFootor(int select)
{
  // при нажатии на Старт - надпись должна измениться на Стоп.

  String text = display.utf8Rus("Старт");
  String colorText = "";
  int coordsX = 22;
  if (selectItem == 3)
  {
    text = "[" + text + "]";
    colorText = COLOR_FOCUS;
  }
  else
  {
    text = " " + text + " ";
    colorText = COLOR_TEXT;
  }

  char buffer[20];
  sprintf(buffer, "%s", text);
  display.drawText(
      buffer,
      colorText,
      COLOR_HIGHLIGHTED,
      coordsX,
      80,
      2);
}
