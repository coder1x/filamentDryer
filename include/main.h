#include <Wire.h>
#include "ClockDryer.h"
#include "TemperatureSensor.h"
#include "Display.h"
#include "Button.h"
using namespace std;

// -- кнопки
#define KEY_LEFT 27
#define KEY_RIGHT 12
#define KEY_SELECT 14
#define KEY_ENTER 26

Button buttonLeft(KEY_LEFT);
Button buttonRight(KEY_RIGHT);
Button buttonSelect(KEY_SELECT);
Button buttonEnter(KEY_ENTER);

// -- Реле

// -- Дисплей
Display display;
#define COLOR_TEXT "#FF6600"
#define COLOR_FOCUS "#FFD800"
#define COLOR_HIGHLIGHTED "#000000"
#define COLOR_LINE "#A0A0A0"

// -- таймер
ClockDryer clockDryer;

// -- сенсор
TemperatureSensor sensor;

// -- Функции
void showHeader();
void showTimer(int select);
void showTemperature(int select);
void showFootor(int select);
void handleButtonSelect();
void handleButtonEnter();
void handleButtonRight();
void handleButtonLeft();

// -- переменные
int hour = 0;
int minutes = 0;
int seconds = 0;
int maxTemperature = 0;
volatile int selectItem = 0;