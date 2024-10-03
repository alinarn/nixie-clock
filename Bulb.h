#ifndef Bulb_h
#define Bulb_h

#include "Arduino.h"

class Bulb {
  private:
    int powerPin;
    int numberPins[4];
    
  public:
    Bulb(int powerPin, const int numberPins[4]);

    void turnOn();
    void turnOff();
    void showDigit(int digit);
};

#endif