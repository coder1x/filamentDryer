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
  uint8_t getTemperature();
  void showTemperature(
      volatile uint8_t *selectItem,
      String colorFocus,
      String color,
      String colorBackground);
  void editeTemperature(
      volatile uint8_t *selectTemperature,
      String color,
      String colorBackground,
      bool isVisible = true);
  uint8_t getMaxTemperature();
  void changeNumber(
      volatile int8_t *plusMinus,
      volatile uint8_t *selectTimer);
  void clearData();

private:
  Display *display;
  GyverMAX6675<CLK_PIN, DATA_PIN, CS_PIN> sens; // указываем пины в порядке SCK SO CS

  void ubdateClockFace();
  void validationTemperature();
  String inputNumber(String numberText, volatile int8_t *plusMinus);

  bool isLockMilis = false;
  uint32_t timerTemperature = 0;
  uint8_t maxTemperature = 0;
  uint8_t currentTemperature = 0;
  String temperatureText[2] = {"0", "0"};
};

#endif