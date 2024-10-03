#ifndef Display_h
#define Display_h

#include "Bulb.h"

class Display {
  private:
    static const int bulbCount = 4;
    Bulb bulbs[bulbCount];

  public:
    Display();
    void displayNumber(int digits[]);
    void turnOnBulb(int index);
    void turnOffBulb(int index);
};

#endif