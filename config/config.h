#ifndef CONFIG_H
#define CONFIG_H

#include "secrets.h"

const unsigned short ON_INTERVAL = 1;
const unsigned short OFF_INTERVAL = 3;
const unsigned long CYCLE_INTERVAL = 3660000; // 1 hour 1 min in milliseconds
const char SSID[] = SECRET_SSID;
const char PASS[] = SECRET_PASS;

// Left to right
// Bulb1
const int BULB1_POWER_PIN = 13;
//order DCBA
const int BULB1_NUMBER_PINS[] = {11, 9, 10, 12};
// Bulb2
const int BULB2_POWER_PIN = 14;
const int BULB2_NUMBER_PINS[] = {4, 2, 3, 5};
// Bulb3
const int BULB3_POWER_PIN = 15;
const int BULB3_NUMBER_PINS[] = {7, 17, 8, 6};
// Bulb4
const int BULB4_POWER_PIN = 16;
const int BULB4_NUMBER_PINS[] = {19, 21, 20, 18};

#endif