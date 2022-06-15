#ifndef TemperatureSensor_H
#define TemperatureSensor_H
#include <Arduino.h>
#include <GyverMAX6675.h>
#include "Display.h"
using namespace std;

// -- термодатчик MAX6675
#define CLK_PIN 4   // Пин SCK
#define DATA_PIN 21 // Пин SO
#define CS_PIN 22   // Пин CS

class TemperatureSensor
{
public:
  TemperatureSensor(Display *display);
  int getTemperature();
  void showTemperature(
      volatile int *selectItem,
      String colorFocus,
      String color,
      String colorBackground);
  void editeTemperature(
      volatile int *selectTemperature,
      String color,
      String colorBackground,
      bool isVisible = true);
  int getMaxTemperature();
  void changeNumber(
      volatile int *plusMinus,
      volatile int *selectTimer);
  void clearData();

private:
  Display *display;
  GyverMAX6675<CLK_PIN, DATA_PIN, CS_PIN> sens; // указываем пины в порядке SCK SO CS
  String validationDigital(int number);
  void cursorTemperature(int coordsX, String color, String colorBackground);
  void ubdateClockFace();
  void validationTemperature();
  String inputNumber(String numberText, volatile int *plusMinus);
  bool isLockMilis = false;
  uint32_t timerTemperature = 0;
  int maxTemperature = 0;
  int currentTemperature = 0;
  String temperatureText[2] = {"0", "0"};
};

#endif