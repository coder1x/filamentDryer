#include "helpers.h"

String validationDigital(uint8_t number)
{
  String numberText = String(number);
  if (numberText.length() < 2)
    return "0" + numberText;

  return numberText;
}
