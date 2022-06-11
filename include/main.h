#include <Wire.h>
#include "ClockDryer.h"
#include "TemperatureSensor.h"
#include "Display.h"
#include "Button.h"
using namespace std;

// -- кнопки
Button buttonLeft(27);
Button buttonRight(12);
Button buttonSelect(14);
Button buttonEnter(26);

// -- Реле

// -- Дисплей
Display display;

// -- таймер
ClockDryer clockDryer;

// -- сенсор
TemperatureSensor sensor;

// -- Функции
void showHeader();
void showTimer(int select);
void showTemperature(int select);
void showFootor(int select);
void handleButton();

// -- переменные
int hour = 0;
int minutes = 0;
int seconds = 0;
int maxTemperature = 0;
int selectItem = 0;