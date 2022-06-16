#include "TemperatureSensor.h"
#include "helpers.h"

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

void TemperatureSensor::changeNumber(
    volatile int8_t *plusMinus,
    volatile uint8_t *selectTimer)
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
    volatile uint8_t *selectTemperature,
    String color,
    String colorBackground,
    bool isVisible)
{

  if (*selectTemperature > 2)
    *selectTemperature = 1;

  uint8_t coordsXPrev = 0;
  uint8_t coordsXNext = 0;

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

  display->cursor(coordsXPrev, colorBackground, colorBackground, 46);
  display->cursor(coordsXNext, color, colorBackground, 46);
}

uint8_t TemperatureSensor::getMaxTemperature()
{
  return maxTemperature;
}

uint8_t TemperatureSensor::getTemperature()
{

  if (!isLockMilis)
  {
    isLockMilis = true;
    timerTemperature = millis();
  }

  if ((millis() - timerTemperature) < 1000)
    return 0;
  timerTemperature = millis();

  if (sens.readTemp())
  {
    return sens.getTempInt();
  }

  return 0;
}

void TemperatureSensor::showTemperature(
    volatile uint8_t *selectItem,
    String colorFocus,
    String color,
    String colorBackground)
{

  String text = "MAX T:" + validationDigital(maxTemperature);
  String colorText = "";

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
      4,
      55,
      2);
}

// -- private

void TemperatureSensor::ubdateClockFace()
{
  String textDigit = validationDigital(maxTemperature);
  temperatureText[0] = textDigit[0];
  temperatureText[1] = textDigit[1];
}

void TemperatureSensor::validationTemperature()
{
  if (maxTemperature > 99)
    maxTemperature = 99;

  ubdateClockFace();
}

String TemperatureSensor::inputNumber(String numberText, volatile int8_t *plusMinus)
{
  int8_t newNumber = atoi(numberText.c_str()) + *plusMinus;

  if (newNumber < 0)
    return "9";

  if (newNumber > 9)
    return "0";

  return String(newNumber);
}