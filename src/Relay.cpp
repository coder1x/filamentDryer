#include "Relay.h"

PWMrelay _relay(RELAY_PIN);

Relay::Relay()
{
  _relay.setPeriod(200); // продолжительность нагрева
  _relay.setPWM(255);    // регулятор мощьности 0-255 (соответствует 0-100%)
  _relay.setLevel(LOW);  // по умолчанию выключаем
}

void Relay::stopRelay()
{
  _relay.setPWM(0);
}

void Relay::setMaxTemperature(uint8_t temperature)
{
  maxTemperature = temperature;
}

void Relay::workRelay()
{
  _relay.tick();
}

void Relay::relayControl(uint8_t temperature)
{
  if (temperature < maxTemperature)
  {
    _relay.setPWM(10);
  }
  else
  {
    stopRelay();
  }
}
