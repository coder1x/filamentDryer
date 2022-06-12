
#ifndef ClockDryer_H
#define ClockDryer_H
#include <Arduino.h>
#include "Display.h"

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
      String colorBackground);

private:
  Display *display;
  int hour = 0;
  int minutes = 0;
  int seconds = 0;
  char buffer[20] = "";
  void cursorTimer(
      int coordsX,
      String color,
      String colorBackground);
  String validationDigital(int number);
  // String hourText [] = {"0", "0"};
  // String minutesText[] = {"0", "0"};
  // String secondsText[] = {"0", "0"};
};

#endif