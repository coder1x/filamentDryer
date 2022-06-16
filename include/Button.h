#ifndef Button_H
#define Button_H
#include <Arduino.h>

class Button
{
public:
  Button(uint8_t pin);
  bool click();
  bool press();
  bool onePress();
  void setDelay(uint16_t delay);
  void setDelayPress(uint16_t delay);

private:
  bool isCliked = false;
  bool isPressed = false;
  bool isOnePress = false;

  uint16_t delay = 20;
  uint16_t delayPress = 400;
  uint32_t timerClick = 0;
  uint32_t timerPress = 0;
  uint32_t timerOnePress = 0;
  uint8_t pin = 0;
};

#endif