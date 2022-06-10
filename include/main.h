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
TemperatureSensor objectSensor;
