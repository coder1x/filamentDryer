#ifndef Relay_H
#define Relay_H
#include <Arduino.h>
#include "PWMrelay.h"

#define RELAY_PIN 13

class Relay
{
public:
  Relay();
  void setMaxTemperature(uint8_t temperature);
  void stopRelay();
  void relayControl(uint8_t temperature);

private:
  uint8_t maxTemperature = 0;
};

#endif
