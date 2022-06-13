#ifndef ClockDryer_H
#define ClockDryer_H
#include <Arduino.h>
#include "Display.h"
using namespace std;

class ClockDryer
{
public:
  ClockDryer(Display *display);
  char *startTimer();
  void showTimer(
      volatile int *selectItem,
      String colorFocus,
      String color,
      String colorBackground);
  void editeTimer(
      volatile int *selectTimer,
      String color,
      String colorBackground,
      bool isVisible = true);
  void changeNumber(
      volatile int *plusMinus,
      volatile int *selectTimer);

private:
  Display *display;
  int hour = 0;
  int minutes = 0;
  int seconds = 0;
  // char buffer[20] = "";
  void cursorTimer(
      int coordsX,
      String color,
      String colorBackground);
  String validationDigital(int number);
  String inputNumber(String numberText, volatile int *plusMinus);
  void validationTime();
  String hourText[2] = {"0", "0"};
  String minutesText[2] = {"0", "0"};
  String secondsText[2] = {"0", "0"};
};

#endif