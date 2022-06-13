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
ClockDryer clockDryer(&display);

// -- сенсор
TemperatureSensor sensor;

// -- Функции
void showHeader();
// void showTimer(int select);
void showTemperature(int select);
void showFootor(int select);
void handleButtonSelect();
void handleButtonEnter();
void handleButtonRight();
void handleButtonLeft();
void handleButtonClick();
bool toggle(bool flag);

// -- переменные

int maxTemperature = 0;
volatile bool isTimerEntered = false;      // введён ли таймер
volatile bool isTimerEditing = false;      // режим редактирование таймера
volatile bool isTimerDigitEditing = false; // изменение цифры в таймере
volatile int plusMinus = 0;                // -1 или 1 (определяем инкрементировать или декрементировать число)

volatile bool isLockSelect = false; // блокирует выбор элементов интерфейса
volatile int selectItem = 0;        // выбранный элемент интерфейса
volatile int selectTimer = 1;
volatile bool isEnter = false;
bool isTimerCursorClear = false;

String temperatureText[] = {"0", "0"};
