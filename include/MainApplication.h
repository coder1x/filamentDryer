#ifndef MainApplication_H
#define MainApplication_H
#include <Wire.h>
#include "ClockDryer.h"
#include "TemperatureSensor.h"
#include "Display.h"
#include "Button.h"
using namespace std;

class MainApplication
{
public:
  MainApplication();
  void loop();
  void handleButtonSelect();
  void handleButtonEnter();
  void handleButtonRight();
  void handleButtonLeft();

private:
  void showHeader();
  void showTimer();
  void showTemperature();
  void buttonStart();
  void buttonClear();
  void handleButtonClick();
  bool toggle(bool flag);

  volatile bool isTimerEditing = false;      // режим редактирование таймера
  volatile bool isTimerDigitEditing = false; // изменение цифры в таймере
  volatile int selectTimer = 1;

  volatile bool isEnter = false;
  volatile bool isLockSelect = false; // блокирует выбор элементов интерфейса
  volatile int selectItem = 0;        // выбранный элемент интерфейса
  volatile int plusMinus = 0;         // -1 или 1 (определяем инкрементировать или декрементировать число)
  bool isStarted = false;

  volatile bool isTemperatureEditing = false;      // режим редактирование температуры
  volatile bool isTemperatureDigitEditing = false; // изменение цифры в Макс Т: температуре
  volatile int selectTemperature = 1;
};

#endif