#include "ClockDryer.h"

ClockDryer::ClockDryer()
{
}

char *ClockDryer::startTimer()
{
  static uint32_t clockTime = millis();
  if (millis() - clockTime < 1000)
    return "";
  clockTime = millis();

  ++seconds;
  if (seconds == 60)
  {
    seconds = 0;
    ++minutes;

    if (minutes == 60)
    {
      minutes = 0;
      ++hour;
    }
  }

  buffer[0] = '\0';
  sprintf(buffer, "%s%d%s%d%s%d", " Time: ", hour, " : ", minutes, " : ", seconds);

  return buffer;
}