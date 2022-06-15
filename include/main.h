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
#define COLOR_LINE "#7FC9FF"

// -- таймер
ClockDryer clockDryer(&display);

// -- сенсор
TemperatureSensor sensor(&display);

// -- Функции
void showHeader();
void showTimer();
void showTemperature();
void buttonStart();
void buttonClear();
void handleButtonSelect();
void handleButtonEnter();
void handleButtonRight();
void handleButtonLeft();
void handleButtonClick();
bool toggle(bool flag);

// -- переменные
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
