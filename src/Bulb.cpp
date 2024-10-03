#include "Bulb.h"
#include "../config/bcd.h"

Bulb::Bulb(const int powerPin, const int numberPins[4]) {
  this->powerPin = powerPin;
  pinMode(this->powerPin, OUTPUT);

  for (int i = 0; i < 4; i++) {
    this->numberPins[i] = numberPins[i];
    pinMode(this->numberPins[i], OUTPUT);
  }
}

void Bulb::turnOn() {
  digitalWrite(powerPin, HIGH);
}

void Bulb::turnOff() {
  digitalWrite(powerPin, LOW);
}

void Bulb::passDigit(int digit) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(numberPins[i], bcd[digit][i]);
  }
}