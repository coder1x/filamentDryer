#include "MainApplication.h"
#include "buttonKey.h"

void handleButtonSelect();
void handleButtonEnter();
void handleButtonRight();
void handleButtonLeft();
void handleButtonClick();

MainApplication application;

void setup()
{
  Serial.begin(921600);
  attachInterrupt(digitalPinToInterrupt(KEY_SELECT), handleButtonSelect, FALLING);
  attachInterrupt(digitalPinToInterrupt(KEY_ENTER), handleButtonEnter, FALLING);
  attachInterrupt(digitalPinToInterrupt(KEY_LEFT), handleButtonLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(KEY_RIGHT), handleButtonRight, FALLING);
}

void loop()
{
  for (;;)
  {
    application.loop();
  }
}

//--------------------------- IRAM_ATTR
void IRAM_ATTR handleButtonLeft()
{
  application.handleButtonLeft();
}

void IRAM_ATTR handleButtonRight()
{
  application.handleButtonRight();
}

void IRAM_ATTR handleButtonEnter()
{
  application.handleButtonEnter();
}

void IRAM_ATTR handleButtonSelect()
{
  application.handleButtonSelect();
}
//--------------------------- IRAM_ATTR End.