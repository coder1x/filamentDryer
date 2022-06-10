#include <Wire.h>
#include "ClockDryer.h"
#include "TemperatureSensor.h"
#include "Display.h"
#include "Сontrol.h"
using namespace std;

// -- кнопки
Сontrol buttonLeft(27);
Сontrol buttonRight(12);
Сontrol buttonSelect(14);
Сontrol buttonEnter(26);

// -- Реле

// -- Дисплей
Display display;

// -- таймер
ClockDryer clockDryer;

// -- сенсор
TemperatureSensor objectSensor;
