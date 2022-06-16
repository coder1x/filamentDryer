#include "ClockDryer.h"
#include "helpers.h"

ClockDryer::ClockDryer(Display *display)
{
  this->display = display;
  uint32_t clockTime = millis();
}

void ClockDryer::showTimer(
    volatile uint8_t *selectItem,
    String colorFocus,
    String color,
    String colorBackground,
    bool isStarted)
{

  if (isStarted)
  {
    startTimer();
  }
  else
  {
    clockTime = millis();
  }

  String text = validationDigital(hour) +
                ":" + validationDigital(minutes) +
                ":" + validationDigital(seconds);
  String colorText = "";
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
      5,
      25,
      2);
}

void ClockDryer::clearData()
{
  hour = 0;
  minutes = 0;
  seconds = 0;
  hourText[0] = '0';
  hourText[1] = '0';
  minutesText[0] = '0';
  minutesText[1] = '0';
  secondsText[0] = '0';
  secondsText[1] = '0';
  isBroken = false;
}

void ClockDryer::changeNumber(
    volatile int8_t *plusMinus,
    volatile uint8_t *selectTimer)
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

bool ClockDryer::getStatus()
{
  return isBroken;
}

void ClockDryer::editeTimer(
    volatile uint8_t *selectTimer,
    String color,
    String colorBackground,
    bool isVisible)
{

  if (*selectTimer > 6)
    *selectTimer = 1;

  uint8_t coordsXPrev = 0;
  uint8_t coordsXNext = 0;

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

  display->cursor(coordsXPrev, colorBackground, colorBackground, 17);
  display->cursor(coordsXNext, color, colorBackground, 17);
}

// -- private

void ClockDryer::startTimer()
{
  if (isBroken)
    return;

  if (!isLockMilis)
  {
    isLockMilis = true;
    clockTime = millis();
  }

  uint16_t rest = millis() - clockTime;

  if (rest < 1000)
    return;
  clockTime = millis();

  seconds = seconds - (double)rest / 1000;

  if (seconds < 0)
  {
    seconds = 60 + seconds;
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

String ClockDryer::inputNumber(String numberText, volatile int8_t *plusMinus)
{
  int8_t newNumber = atoi(numberText.c_str()) + *plusMinus;

  if (newNumber < 0)
    return "9";

  if (newNumber > 9)
    return "0";

  return String(newNumber);
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