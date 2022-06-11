#include "main.h"

void clearLine(int y);

void setup()
{
  Serial.begin(921600);
  attachInterrupt(digitalPinToInterrupt(14), handleButton, FALLING);
}

void loop()
{
  // handleButton();
  if (buttonSelect.click())
  {
    ++selectItem;
  }

  showHeader();
  showTimer(selectItem);
  showTemperature(selectItem);
  showFootor(selectItem);
}

void IRAM_ATTR handleButton()
{
  if (buttonSelect.click())
  {
    ++selectItem;
  }

  if (selectItem > 3)
  {
    selectItem = 0;
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
    colorText = "#FFD800";
  }
  else
  {
    text = " " + text + " ";
    colorText = "#FF6600";
  }

  char buffer[30];
  sprintf(buffer, "%s", text);
  display.drawText(
      buffer,
      display.colorHex(colorText),
      display.colorHex("#000000"),
      coordsX,
      25,
      2);
  display.tft.drawLine(
      0,
      43,
      128,
      43,
      display.colorHex("#A0A0A0"));
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
    colorText = "#FFD800";
    text = "[" + text + "]";
  }
  else
  {
    colorText = "#FF6600";
    text = " " + text + " ";
  }

  char buffer[20];
  sprintf(buffer, "%s", text);
  display.drawText(
      buffer,
      display.colorHex(colorText),
      display.colorHex("#000000"),
      coordsX,
      55,
      2);
  display.tft.drawLine(
      0,
      72,
      128,
      72,
      display.colorHex("#A0A0A0"));
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
    colorText = "#FFD800";
  }
  else
  {
    text = " " + text + " ";
    colorText = "#FF6600";
  }

  char buffer[20];
  sprintf(buffer, "%s", text);
  display.drawText(
      buffer,
      display.colorHex(colorText),
      display.colorHex("#000000"),
      coordsX,
      80,
      2);
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
        display.colorHex("#FF6600"),
        display.colorHex("#000000"),
        0,
        2);
    display.tft.drawLine(
        0,
        12,
        128,
        12,
        display.colorHex("#A0A0A0"));
  }
}
