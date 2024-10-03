#include "Display.h"
#include "config.h"

Display::Display()
  : bulbs{
      Bulb(BULB1_POWER_PIN, BULB1_NUMBER_PINS),
      Bulb(BULB2_POWER_PIN, BULB2_NUMBER_PINS),
      Bulb(BULB3_POWER_PIN, BULB3_NUMBER_PINS),
      Bulb(BULB4_POWER_PIN, BULB4_NUMBER_PINS)
    }
{
}

void Display::displayNumber(int digits[]) {
   for (int i = 0; i < bulbCount; i++) {
    bulbs[i].showDigit(digits[i]);
  }
}

void Display::turnOnBulb(int index){
  if (index >= 0 && index < bulbCount) {
    bulbs[index].turnOn();
  }
}

void Display::turnOffBulb(int index){
  if (index >= 0 && index < bulbCount) {
    bulbs[index].turnOff();
  }
}