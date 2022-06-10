#include "Button.h"

Button::Button(int pin)
{
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
}

char *Button::button()
{

  bool btnState = !digitalRead(this->pin);
  if (btnState && !flag && millis() - btnTimer > 10)
  {
    flag = true;
    btnTimer = millis();

    sprintf(buffer, "%s%d", " press: ", this->pin);
    return buffer;
  }

  if (!btnState && flag && millis() - btnTimer > 10)
  {
    flag = false;
    btnTimer = millis();

    sprintf(buffer, "%s%d", " release: ", this->pin);
    return buffer;
  }

  return "";
}