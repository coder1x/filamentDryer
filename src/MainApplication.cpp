#include "MainApplication.h"
#include "buttonKey.h"

Button buttonLeft(KEY_LEFT);
Button buttonRight(KEY_RIGHT);
Button buttonSelect(KEY_SELECT);
Button buttonEnter(KEY_ENTER);

Display display;
ClockDryer clockDryer(&display);
TemperatureSensor sensor(&display);

Relay relay;

// -- Дисплей
#define COLOR_TEXT "#7FC9FF"
#define COLOR_FOCUS "#FFFFFF"
#define COLOR_HIGHLIGHTED "#000000"
#define COLOR_LINE "#FF6600"

MainApplication::MainApplication()
{
}

void MainApplication::loop()
{
  for (;;)
  {
    handleButtonClick();
    showHeader();
    showTimer();
    showTemperature();
    buttonStart();
    buttonClear();
    relay.workRelay();

    if (!isStartApplication)
      isStartApplication = true;
  }
}

//--------------------------- IRAM_ATTR

void MainApplication::selectElement()
{
  switch (selectItem)
  {
  case 1:
    isTimerDigitEditing = true;
    break;
  case 2:
    isTemperatureDigitEditing = true;
    break;
  default:
    break;
  }
}

void MainApplication::handleButtonLeft()
{
  const bool isUnlocked = !isStarted && isLockSelect;
  if (buttonLeft.click() && isUnlocked)
  {
    selectElement();
    plusMinus = -1;
  }
}

void MainApplication::handleButtonRight()
{
  const bool isUnlocked = !isStarted && isLockSelect;
  if (buttonRight.click() && isUnlocked)
  {
    selectElement();
    plusMinus = 1;
  }
}

void MainApplication::handleButtonEnter()
{
  if (!buttonEnter.click())
    return;

  isEnter = true;

  switch (selectItem)
  {
  case 0:
    isEnter = false;
    isLockSelect = true;
    break;
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

void MainApplication::handleButtonSelect()
{
  if (!buttonSelect.click())
    return;

  if (isTimerEditing)
    ++selectTimer;

  if (isTemperatureEditing)
    ++selectTemperature;

  if (isLockSelect)
    return;

  ++selectItem;
  if (selectItem > 4)
    selectItem = 1;
}
//--------------------------- IRAM_ATTR End.

void MainApplication::handleButtonClick()
{
  handleButtonSelect();
  handleButtonLeft();
  handleButtonRight();
  handleButtonEnter();
}

void MainApplication::showHeader()
{
  uint8_t currentTemperature = sensor.getTemperature();
  if (currentTemperature == 0)
    return;

  if (isStarted)
    relay.relayControl(currentTemperature);

  if (cacheTemperature == currentTemperature)
    return;

  cacheTemperature = currentTemperature;

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

void MainApplication::showTimer()
{
  if (isTimerFocused && selectItem != 1)
  {
    isTimerFocused = false;
  }
  else if (isStartApplication && !isStarted && selectItem != 1)
    return;

  const bool isEditing = !isTimerEditing && !isTimerDigitEditing && !isEnter;
  if (isTimerFocused && selectItem == 1 && isEditing)
    return;

  clockDryer.showTimer(
      &selectItem,
      COLOR_FOCUS,
      COLOR_TEXT,
      COLOR_HIGHLIGHTED,
      isStarted);

  if (selectItem == 1)
  {
    isTimerFocused = true;
  }

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
      relay.stopRelay();
      isStarted = false;
      isLockSelect = false;
      isButtonStartFocused = false;
    }
  }

  display.tft.drawLine(
      0,
      43,
      128,
      43,
      display.colorHex(COLOR_LINE));
}

void MainApplication::showTemperature()
{

  if (isTemperatureFocused && selectItem != 2)
  {
    isTemperatureFocused = false;
  }
  else if (isStartApplication && selectItem != 2)
    return;

  const bool isEditing = !isTemperatureEditing && !isTemperatureDigitEditing && !isEnter;
  if (isTemperatureFocused && selectItem == 2 && isEditing)
    return;

  sensor.showTemperature(
      &selectItem,
      COLOR_FOCUS,
      COLOR_TEXT,
      COLOR_HIGHLIGHTED);

  if (selectItem == 2)
  {
    isTemperatureFocused = true;
  }

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

String MainApplication::toggleFocus(String *text, uint8_t item)
{
  if (selectItem == item)
  {
    *text = "[" + *text + "]";
    return COLOR_FOCUS;
  }
  else
  {
    *text = " " + *text + " ";
    return COLOR_TEXT;
  }
}

void MainApplication::buttonStart()
{

  if (isButtonStartFocused && selectItem != 3)
  {
    isButtonStartFocused = false;
  }
  else if (isStartApplication && selectItem != 3)
    return;

  if (isButtonStartFocused && selectItem == 3 && !isEnter)
    return;

  String text = display.utf8Rus(isStarted ? "Стоп " : "Старт");
  String color = toggleFocus(&text, 3);
  char buffer[20];
  sprintf(buffer, "%s", text);
  display.drawText(
      buffer,
      color,
      COLOR_HIGHLIGHTED,
      22,
      80,
      2);

  if (selectItem == 3)
  {
    isButtonStartFocused = true;
  }

  if (isStarted)
  {
    relay.setMaxTemperature(sensor.getMaxTemperature());
  }
  else
  {
    relay.stopRelay();
  }

  if (selectItem == 3 && isEnter)
  {
    isStarted = toggle(isStarted);
    isEnter = false;
    isButtonStartFocused = false;
  }
}

void MainApplication::buttonClear()
{
  if (selectItem == selectButtonClear && !isEnter)
    return;

  String text = display.utf8Rus("Сброс");
  String color = toggleFocus(&text, 4);
  char buffer[20];
  sprintf(buffer, "%s", text);
  display.drawText(
      buffer,
      color,
      COLOR_HIGHLIGHTED,
      22,
      104,
      2);

  if (selectItem == 4 && isEnter)
  {
    isEnter = false;
    isLockSelect = false;
    isTimerFocused = true;
    isTemperatureFocused = true;
    sensor.clearData();
    clockDryer.clearData();
  }

  selectButtonClear = selectItem;
}

bool MainApplication::toggle(bool flag)
{
  return flag ? false : true;
}