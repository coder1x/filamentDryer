#ifndef ClockDryer_H
#define ClockDryer_H
#include <Arduino.h>
#include "Display.h"
using namespace std;

class ClockDryer
{
public:
  ClockDryer(Display *display);
  void showTimer(
      volatile uint8_t *selectItem,
      String colorFocus,
      String color,
      String colorBackground,
      bool isStarted);
  void editeTimer(
      volatile uint8_t *selectTimer,
      String color,
      String colorBackground,
      bool isVisible = true);
  void changeNumber(
      volatile int8_t *plusMinus,
      volatile uint8_t *selectTimer);
  bool getStatus();
  void clearData();

private:
  String inputNumber(String numberText, volatile int8_t *plusMinus);
  void validationTime();
  void startTimer();
  void ubdateClockFace();

  Display *display;

  double hour = 0;
  double minutes = 0;
  double seconds = 0;

  uint32_t clockTime = 0;
  String hourText[2] = {"0", "0"};
  String minutesText[2] = {"0", "0"};
  String secondsText[2] = {"0", "0"};

  bool isLockMilis = false;
  bool isBroken = false;
};

#endif