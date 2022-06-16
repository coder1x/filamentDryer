#include "Relay.h"

PWMrelay _relay(RELAY_PIN);

Relay::Relay()
{
  _relay.setPeriod(1000); // установка периода ШИМ в миллисекундах. 1000 соответствует 1 Гц
  _relay.setPWM(255);     // установка заполнения шим, 0-255 (соответствует 0-100%)
  _relay.setLevel(LOW);   // по умолчанию выключаем что бы потом быстро включать.
}

void Relay::stopRelay()
{
  _relay.setPWM(0);
}

void Relay::setMaxTemperature(uint8_t temperature)
{
  maxTemperature = temperature;
}

void Relay::relayControl(uint8_t temperature)
{
  if (temperature < maxTemperature)
  {
    _relay.setPWM(50);
  }
  else
  {
    stopRelay();
  }
  _relay.tick();
}
