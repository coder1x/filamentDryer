#ifndef Сontrol_H
#define Сontrol_H
#include <Arduino.h>

class Сontrol
{
public:
  Сontrol(int pin);
  char *button();

private:
  int buttonState = 0;
  bool flag = false;
  uint32_t btnTimer = 0;
  int pin = 0;
  char buffer[20] = "";
};

#endif