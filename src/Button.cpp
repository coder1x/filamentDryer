#include "Button.h"

Button::Button(uint8_t pin)
{
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
}

bool Button::click()
{
  const bool buttonState = !digitalRead(this->pin);
  const bool isTime = (millis() - timerClick) > delay;

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
  const bool buttonState = !digitalRead(this->pin);
  const bool isTime = (millis() - timerPress) > delayPress;

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
  const bool buttonState = !digitalRead(this->pin);
  const bool isTime = (millis() - timerOnePress) > delay;

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

void Button::setDelay(uint16_t delay)
{
  this->delay = delay;
}
void Button::setDelayPress(uint16_t delay)
{
  delayPress = delay;
}