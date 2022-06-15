#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(Display *display)
{
  this->display = display;
  uint32_t timerTemperature = millis();
}

void TemperatureSensor::clearData()
{
  maxTemperature = 0;
  currentTemperature = 0;
  temperatureText[0] = '0';
  temperatureText[1] = '0';
}

String TemperatureSensor::validationDigital(int number)
{
  String numberText = String(number);
  if (numberText.length() < 2)
    return "0" + numberText;

  return numberText;
}

void TemperatureSensor::cursorTemperature(
    int coordsX,
    String color,
    String colorBackground)
{
  display->drawText(
      "*",
      color,
      colorBackground,
      coordsX,
      46,
      1);
}

void TemperatureSensor::validationTemperature()
{
  if (maxTemperature > 99)
    maxTemperature = 99;

  ubdateClockFace();
}

void TemperatureSensor::ubdateClockFace()
{
  String textDigit = validationDigital(maxTemperature);
  temperatureText[0] = textDigit[0];
  temperatureText[1] = textDigit[1];
}

String TemperatureSensor::inputNumber(String numberText, volatile int *plusMinus)
{
  int newNumber = 0;
  newNumber = atoi(numberText.c_str()) + *plusMinus;

  if (newNumber < 0)
    return String(9);

  if (newNumber > 9)
    return String(0);

  return String(newNumber);
}

void TemperatureSensor::changeNumber(
    volatile int *plusMinus,
    volatile int *selectTimer)
{

  switch (*selectTimer)
  {
  case 1:
    temperatureText[0] = inputNumber(temperatureText[0], plusMinus);
    maxTemperature = atoi((temperatureText[0] + temperatureText[1]).c_str());
    break;
  case 2:
    temperatureText[1] = inputNumber(temperatureText[1], plusMinus);
    maxTemperature = atoi((temperatureText[0] + temperatureText[1]).c_str());
    break;

  default:
    break;
  }

  validationTemperature();
}

void TemperatureSensor::editeTemperature(
    volatile int *selectTemperature,
    String color,
    String colorBackground,
    bool isVisible)
{

  if (*selectTemperature > 2)
    *selectTemperature = 1;

  int coordsXPrev = 0;
  int coordsXNext = 0;

  switch (*selectTemperature)
  {
  case 1:
    coordsXPrev = 103;
    coordsXNext = 91;
    break;
  case 2:
    coordsXPrev = 91;
    coordsXNext = 103;
    break;

  default:
    break;
  }

  if (!isVisible)
    color = colorBackground;

  cursorTemperature(coordsXPrev, colorBackground, colorBackground);
  cursorTemperature(coordsXNext, color, colorBackground);
}

int TemperatureSensor::getMaxTemperature()
{
  return maxTemperature;
}

int TemperatureSensor::getTemperature()
{

  if (!isLockMilis)
  {
    isLockMilis = true;
    timerTemperature = millis();
  }

  uint32_t rest = millis() - timerTemperature;

  if (rest < 1000)
    return 0;
  timerTemperature = millis();

  if (sens.readTemp())
  {
    return sens.getTempInt();
  }

  return 0;
}

void TemperatureSensor::showTemperature(
    volatile int *selectItem,
    String colorFocus,
    String color,
    String colorBackground)
{

  String text = "MAX T:" + validationDigital(maxTemperature);
  String colorText = "";
  int coordsX = 4;
  if (*selectItem == 2)
  {
    colorText = colorFocus;
    text = "[" + text + "]";
  }
  else
  {
    colorText = color;
    text = " " + text + " ";
  }

  char buffer[20];
  sprintf(buffer, "%s", text);
  display->drawText(
      buffer,
      colorText,
      colorBackground,
      coordsX,
      55,
      2);
}