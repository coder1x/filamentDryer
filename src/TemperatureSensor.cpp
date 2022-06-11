#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor()
{
}

int TemperatureSensor::getTemperature()
{
  static uint32_t timerTemperature = millis();
  if (millis() - timerTemperature < 1000)
    return 0;
  timerTemperature = millis();

  if (sens.readTemp())
  {
    return sens.getTempInt();
  }

  return 0;
}