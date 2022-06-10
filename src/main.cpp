#include "main.h"

void clearLine(int y);

void setup()
{
  Serial.begin(921600);
}

void loop()
{

  //-------------------------------- Сенсор

  char *temperatureText = objectSensor.sensor();

  if (temperatureText != "")
  {
    display.drawtext(
        temperatureText,
        display.colorHex("#FF6600"),
        display.colorHex("#000000"),
        0,
        5);
    display.tft.drawLine(
        0,
        15,
        128,
        15,
        display.colorHex("#FFFFFF"));
  }

  //-------------------------------- Таймер

  char *timeText = clockDryer.startTimer();

  if (timeText != "")
    display.drawtext(
        timeText,
        display.colorHex("#FF6600"),
        display.colorHex("#000000"),
        0,
        25);

  //-------------------------------- Кнопки

  // bool isClicked = buttonLeft.click();
  // if (isClicked)
  // {
  //   clearLine(35);
  //   display.drawtext(
  //       "buttonLeft",
  //       display.colorHex("#FF6600"),
  //       display.colorHex("#000000"),
  //       0,
  //       35);
  // }
  // else
  // {
  //   clearLine(35);
  // }

  // buttonText = buttonRight.button();
  // if (buttonText != "")
  // {
  //   clearLine(35);
  //   display.drawtext(
  //       buttonText,
  //       display.colorHex("#FF6600"),
  //       display.colorHex("#000000"),
  //       0,
  //       35);
  // }

  // buttonText = buttonSelect.button();
  // if (buttonText != "")
  // {
  //   clearLine(35);
  //   display.drawtext(
  //       buttonText,
  //       display.colorHex("#FF6600"),
  //       display.colorHex("#000000"),
  //       0,
  //       35);
  // }

  // buttonText = buttonEnter.button();
  // if (buttonText != "")
  // {
  //   clearLine(35);
  //   display.drawtext(
  //       buttonText,
  //       display.colorHex("#FF6600"),
  //       display.colorHex("#000000"),
  //       0,
  //       35);
  // }

  //-------------------------------- Реле
}

void clearLine(int y)
{
  display.drawtext(
      "                                ",
      display.colorHex("#FF6600"),
      display.colorHex("#000000"),
      0,
      y);
}