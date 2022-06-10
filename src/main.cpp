#include "main.h"

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

  char *buttonText = buttonLeft.button();
  if (buttonText != "")
    display.drawtext(
        buttonText,
        display.colorHex("#FF6600"),
        display.colorHex("#000000"),
        0,
        35);

  buttonText = buttonRight.button();
  if (buttonText != "")
    display.drawtext(
        buttonText,
        display.colorHex("#FF6600"),
        display.colorHex("#000000"),
        0,
        35);

  buttonText = buttonSelect.button();
  if (buttonText != "")
    display.drawtext(
        buttonText,
        display.colorHex("#FF6600"),
        display.colorHex("#000000"),
        0,
        35);

  buttonText = buttonEnter.button();
  if (buttonText != "")
    display.drawtext(
        buttonText,
        display.colorHex("#FF6600"),
        display.colorHex("#000000"),
        0,
        35);

  //-------------------------------- Реле
}