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
  handleButtonClick();
  showHeader();
  showTimer();
  showTemperature();
  buttonStart();
  buttonClear();
}

//--------------------------- IRAM_ATTR
void IRAM_ATTR handleButtonLeft()
{
  if (buttonLeft.click() && !isStarted && isLockSelect)
  {
    switch (selectItem)
    {
    case 1: // установка таймера
      isTimerDigitEditing = true;
      break;
    case 2: // установка максимальной температуры
      isTemperatureDigitEditing = true;
      break;
    default:
      break;
    }

    plusMinus = -1;
  }
}

void IRAM_ATTR handleButtonRight()
{
  if (buttonRight.click() && !isStarted && isLockSelect)
  {

    switch (selectItem)
    {
    case 1: // установка таймера
      isTimerDigitEditing = true;
      break;
    case 2: // установка максимальной температуры
      isTemperatureDigitEditing = true;
      break;
    default:
      break;
    }

    plusMinus = 1;
  }
}

void IRAM_ATTR handleButtonEnter()
{
  if (!buttonEnter.click())
    return;

  isEnter = true;

  switch (selectItem)
  {
  case 1: // установка таймера
    isTimerEditing = toggle(isTimerEditing);
    break;
  case 2: // установка максимальной температуры
    isTemperatureEditing = toggle(isTemperatureEditing);
    break;
  default:
    break;
  }

  isLockSelect = toggle(isLockSelect);
}

void IRAM_ATTR handleButtonSelect()
{
  const bool isSelect = buttonSelect.click();
  if (isSelect && !isLockSelect)
    ++selectItem;

  if (isSelect && isTimerEditing)
    ++selectTimer;

  if (isSelect && isTemperatureEditing)
    ++selectTemperature;

  if (selectItem > 4)
    selectItem = 1;
}
//--------------------------- IRAM_ATTR End.

void handleButtonClick()
{
  handleButtonSelect();
  handleButtonLeft();
  handleButtonRight();
  handleButtonEnter();
}

void showHeader()
{
  int currentTemperature = sensor.getTemperature();
  if (currentTemperature != 0)
  {
    char buffer[20];
    sprintf(buffer, "%s%d%s", display.utf8Rus("температура: "), currentTemperature, " C");
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

void showTimer()
{
  clockDryer.showTimer(
      &selectItem,
      COLOR_FOCUS,
      COLOR_TEXT,
      COLOR_HIGHLIGHTED,
      isStarted);

  if (isTimerEditing && selectItem == 1)
  {
    clockDryer.editeTimer(
        &selectTimer,
        COLOR_TEXT,
        COLOR_HIGHLIGHTED);

    if (isTimerDigitEditing)
    {
      clockDryer.changeNumber(
          &plusMinus,
          &selectTimer);
      isTimerDigitEditing = false;
    }
  }
  else
  {
    if (selectItem == 1 && isEnter)
    {
      isEnter = false;
      clockDryer.editeTimer(
          &selectTimer,
          COLOR_TEXT,
          COLOR_HIGHLIGHTED, false);
    }

    if (clockDryer.getStatus())
    {
      isStarted = false;
      isLockSelect = false;
    }
  }

  display.tft.drawLine(
      0,
      43,
      128,
      43,
      display.colorHex(COLOR_LINE));
}

void showTemperature()
{
  sensor.showTemperature(
      &selectItem,
      COLOR_FOCUS,
      COLOR_TEXT,
      COLOR_HIGHLIGHTED);

  if (isTemperatureEditing && selectItem == 2)
  {
    sensor.editeTemperature(
        &selectTemperature,
        COLOR_TEXT,
        COLOR_HIGHLIGHTED);

    if (isTemperatureDigitEditing)
    {
      sensor.changeNumber(
          &plusMinus,
          &selectTemperature);
      isTemperatureDigitEditing = false;
    }
  }
  else
  {
    if (selectItem == 2 && isEnter)
    {
      isEnter = false;
      sensor.editeTemperature(
          &selectTemperature,
          COLOR_TEXT,
          COLOR_HIGHLIGHTED, false);
    }
  }

  display.tft.drawLine(
      0,
      72,
      128,
      72,
      display.colorHex(COLOR_LINE));
}

void buttonStart()
{
  String text = display.utf8Rus(isStarted ? "Стоп " : "Старт");
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

  if (selectItem == 3 && isEnter)
  {
    isStarted = toggle(isStarted);
    isEnter = false;
  }
}

void buttonClear()
{
  String text = display.utf8Rus("Сброс");
  String colorText = "";
  int coordsX = 22;
  if (selectItem == 4)
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
      104,
      2);

  if (selectItem == 4 && isEnter)
  {
    isEnter = false;
    isLockSelect = false;
    sensor.clearData();
    clockDryer.clearData();
  }
}

bool toggle(bool flag)
{
  return flag ? false : true;
}