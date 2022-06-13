#include "ClockDryer.h"

ClockDryer::ClockDryer(Display *display)
{
  this->display = display;
}

void ClockDryer::cursorTimer(
    int coordsX,
    String color,
    String colorBackground)
{
  display->drawText(
      "*",
      color,
      colorBackground,
      coordsX,
      17,
      1);
}

String ClockDryer::inputNumber(String numberText, volatile int *plusMinus)
{
  int newNumber = 0;
  newNumber = atoi(numberText.c_str()) + *plusMinus;

  if (newNumber < 0)
    return String(9);

  if (newNumber > 9)
    return String(0);

  return String(newNumber);
}

void ClockDryer::changeNumber(
    volatile int *plusMinus,
    volatile int *selectTimer)
{

  switch (*selectTimer)
  {
  case 1:
    hourText[0] = inputNumber(hourText[0], plusMinus);
    hour = atoi((hourText[0] + hourText[1]).c_str());
    break;
  case 2:
    hourText[1] = inputNumber(hourText[1], plusMinus);
    hour = atoi((hourText[0] + hourText[1]).c_str());
    break;
  case 3:
    minutesText[0] = inputNumber(minutesText[0], plusMinus);
    minutes = atoi((minutesText[0] + minutesText[1]).c_str());
    break;
  case 4:
    minutesText[1] = inputNumber(minutesText[1], plusMinus);
    minutes = atoi((minutesText[0] + minutesText[1]).c_str());
    break;
  case 5:
    secondsText[0] = inputNumber(secondsText[0], plusMinus);
    seconds = atoi((secondsText[0] + secondsText[1]).c_str());
    break;
  case 6:
    secondsText[1] = inputNumber(secondsText[1], plusMinus);
    seconds = atoi((secondsText[0] + secondsText[1]).c_str());
    break;

  default:
    break;
  }

  validationTime();
}

void ClockDryer::validationTime()
{
  if (seconds > 60)
  {
    seconds = seconds - 60;
    ++minutes;
  }

  if (minutes > 60)
  {
    minutes = minutes - 60;
    ++hour;
  }

  if (hour > 99)
    hour = 99;

  ubdateClockFace();

  isBroken = false;
}

void ClockDryer::ubdateClockFace()
{
  String textDigit = validationDigital(hour);
  hourText[0] = textDigit[0];
  hourText[1] = textDigit[1];

  textDigit = validationDigital(minutes);
  minutesText[0] = textDigit[0];
  minutesText[1] = textDigit[1];

  textDigit = validationDigital(seconds);
  secondsText[0] = textDigit[0];
  secondsText[1] = textDigit[1];
}

bool ClockDryer::getStatus()
{
  return isBroken;
}

void ClockDryer::editeTimer(
    volatile int *selectTimer,
    String color,
    String colorBackground,
    bool isVisible)
{

  if (*selectTimer > 6)
    *selectTimer = 1;

  int coordsXPrev = 0;
  int coordsXNext = 0;

  switch (*selectTimer)
  {
  case 1:
    coordsXPrev = 104;
    coordsXNext = 20;
    break;
  case 2:
    coordsXPrev = 20;
    coordsXNext = 32;
    break;
  case 3:
    coordsXPrev = 32;
    coordsXNext = 56;
    break;
  case 4:
    coordsXPrev = 56;
    coordsXNext = 68;
    break;
  case 5:
    coordsXPrev = 68;
    coordsXNext = 92;
    break;
  case 6:
    coordsXPrev = 92;
    coordsXNext = 104;
    break;

  default:
    break;
  }

  if (!isVisible)
    color = colorBackground;

  cursorTimer(coordsXPrev, colorBackground, colorBackground);
  cursorTimer(coordsXNext, color, colorBackground);
}

String ClockDryer::validationDigital(int number)
{
  String numberText = String(number);
  if (numberText.length() < 2)
    return "0" + numberText;

  return numberText;
}

void ClockDryer::showTimer(
    volatile int *selectItem,
    String colorFocus,
    String color,
    String colorBackground,
    bool isStarted)
{

  if (isStarted)
  {
    startTimer();
  }

  String hourText = validationDigital(hour);
  String minutesText = validationDigital(minutes);
  String secondsText = validationDigital(seconds);

  String text = hourText + ":" + minutesText + ":" + secondsText;
  String colorText = "";
  int coordsX = 5;
  if (*selectItem == 1)
  {
    text = "[" + text + "]";
    colorText = colorFocus;
  }
  else
  {
    text = " " + text + " ";
    colorText = color;
  }

  char buffer[30];
  sprintf(buffer, "%s", text);
  display->drawText(
      buffer,
      colorText,
      colorBackground,
      coordsX,
      25,
      2);
}

void ClockDryer::startTimer()
{
  if (isBroken)
    return;
  static uint32_t clockTime = millis();
  if (millis() - clockTime < 1000)
    return;
  clockTime = millis();

  --seconds;
  if (seconds < 0)
  {
    seconds = 59;
    --minutes;

    if (minutes < 0)
    {
      minutes = 59;
      --hour;

      if (hour < 0)
      {
        isBroken = true;
        hour = 0;
        minutes = 0;
        seconds = 0;
      }
    }
  }

  ubdateClockFace();
}