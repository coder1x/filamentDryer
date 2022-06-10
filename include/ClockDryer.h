
#ifndef ClockDryer_H
#define ClockDryer_H
#include <Arduino.h>

class ClockDryer
{
public:
  ClockDryer();
  char *startTimer();

private:
  int hour = 0;
  int minutes = 0;
  int seconds = 0;
  char buffer[20] = "";
};

#endif