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
  timer();

  showTemperature();
  showFootor();
}

//--------------------------- IRAM_ATTR
void IRAM_ATTR handleButtonLeft()
{
  if (buttonLeft.click())
  {
    isTimerDigitEditing = true;
    plusMinus = -1;
  }
}

void IRAM_ATTR handleButtonRight()
{
  if (buttonRight.click())
  {
    isTimerDigitEditing = true;
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
    break;
  case 3: // кнопка старта
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

  if (selectItem > 3)
    selectItem = 0;
}
//--------------------------- IRAM_ATTR End.

void timer()
{
  clockDryer.showTimer(
      &selectItem,
      COLOR_FOCUS,
      COLOR_TEXT,
      COLOR_HIGHLIGHTED,
      isStarted);

  if (isTimerEditing)
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

void handleButtonClick()
{
  const bool isSelect = buttonSelect.click();

  if (isSelect && !isLockSelect)
    ++selectItem;

  if (isSelect && isTimerEditing)
    ++selectTimer;

  if (buttonLeft.click())
  {
    isTimerDigitEditing = true;
    plusMinus = -1;
  }

  if (buttonRight.click())
  {
    isTimerDigitEditing = true;
    plusMinus = 1;
  }
}

void showHeader()
{

  currentTemperature = sensor.getTemperature();
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

void showTemperature()
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

void showFootor()
{
  // при нажатии на Старт - надпись должна измениться на Стоп.

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

bool toggle(bool flag)
{
  return flag ? false : true;
}