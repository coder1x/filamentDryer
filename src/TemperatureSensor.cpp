#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor()
{
}

char *TemperatureSensor::sensor()
{

  static uint32_t timerTemperature = millis();
  if (millis() - timerTemperature < 1000)
    return "";
  timerTemperature = millis();

  buffer[0] = '\0';

  if (sens.readTemp())
  { // Читаем температуру

    const int temp = sens.getTempInt();

    sprintf(buffer, "%s%d%s", " Temperature: ", temp, " C");
    return buffer;
  }
  else
  {
    sprintf(buffer, "%s", " Error Temp ");
    return buffer;
  }
}