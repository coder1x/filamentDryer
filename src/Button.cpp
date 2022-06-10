#include "Button.h"

Button::Button(int pin)
{
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
}

bool Button::click()
{
  bool buttonState = !digitalRead(this->pin);
  const int time = millis() - timerClick;
  const bool isTime = time > delay;

  if (buttonState && !isCliked && isTime)
  { // нажали кнопку
    isCliked = true;
    timerClick = millis();
  }

  if (!buttonState && isCliked && isTime)
  { // произашёл клик (отпустили кнопку)
    isCliked = false;
    timerClick = millis();
    return true;
  }

  return false;
}

bool Button::press()
{
  bool buttonState = !digitalRead(this->pin);
  const int time = millis() - timerPress;
  const bool isTime = time > delayPress;

  if (buttonState && isTime)
  { // нажали кнопку
    isPressed = true;
    timerPress = millis();
    return isPressed;
  }

  if (!buttonState)
    isPressed = false;

  return isPressed;
}

bool Button::onePress()
{
  bool buttonState = !digitalRead(this->pin);
  const int time = millis() - timerOnePress;
  const bool isTime = time > delay;

  if (buttonState && !isOnePress && isTime)
  { // нажали кнопку
    isOnePress = true;
    timerOnePress = millis();
    return true;
  }

  if (!buttonState)
    isOnePress = false;

  return false;
}

void Button::setDelay(int delay)
{
  this->delay = delay;
}
void Button::setDelayPress(int delay)
{
  delayPress = delay;
}