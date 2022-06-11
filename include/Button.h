#ifndef Button_H
#define Button_H
#include <Arduino.h>

class Button
{
public:
  Button(int pin);
  bool click();
  bool press();
  bool onePress();
  void setDelay(int delay);
  void setDelayPress(int delay);

private:
  int delay = 50;
  int delayPress = 400;
  bool isCliked = false;
  bool isPressed = false;
  bool isOnePress = false;
  uint32_t timerClick = 0;
  uint32_t timerPress = 0;
  uint32_t timerOnePress = 0;
  int pin = 0;
};

#endif