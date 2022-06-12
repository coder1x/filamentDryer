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
  const bool isSelect = buttonSelect.click();

  if (isSelect && !isLockSelect)
    ++selectItem;

  if (isSelect && isTimerEditing)
    ++selectTimer;

  showHeader();

  // --------------------- Таймер
  clockDryer.showTimer(
      &selectItem,
      COLOR_FOCUS,
      COLOR_TEXT,
      COLOR_HIGHLIGHTED);

  if (isTimerEditing)
    clockDryer.editeTimer(
        &selectTimer,
        COLOR_TEXT,
        COLOR_HIGHLIGHTED);

  display.tft.drawLine(
      0,
      43,
      128,
      43,
      display.colorHex(COLOR_LINE));
  // --------------------- Таймер end.

  showTemperature(selectItem);
  showFootor(selectItem);
}

void IRAM_ATTR handleButtonLeft()
{
}

void IRAM_ATTR handleButtonRight()
{
}

void IRAM_ATTR handleButtonEnter()
{
  if (buttonEnter.click())
    switch (selectItem)
    {
    case 1: // установка таймера
      isTimerEditing = true;
      isLockSelect = true;
      isSelectEdit = true;
      break;
    case 2: // установка максимальной температуры
      break;
    case 3: // кнопка старта
      break;
    default:
      break;
    }
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

void showHeader()
{
  int temperature = sensor.getTemperature();
  if (temperature != 0)
  {
    char buffer[20];
    sprintf(buffer, "%s%d%s", display.utf8Rus("температура: "), temperature, " C");
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

void showFootor(int select)
{
  // при нажатии на Старт - надпись должна измениться на Стоп.

  String text = display.utf8Rus("Старт");
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
}
