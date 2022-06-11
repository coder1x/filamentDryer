#ifndef TemperatureSensor_H
#define TemperatureSensor_H
#include <Arduino.h>
#include <GyverMAX6675.h>

// -- термодатчик MAX6675
#define CLK_PIN 4   // Пин SCK
#define DATA_PIN 21 // Пин SO
#define CS_PIN 22   // Пин CS

class TemperatureSensor
{
public:
  TemperatureSensor();
  int getTemperature();

private:
  GyverMAX6675<CLK_PIN, DATA_PIN, CS_PIN> sens; // указываем пины в порядке SCK SO CS
};

#endif