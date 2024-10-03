#include "TimeManager.h"

TimeManager::TimeManager(WiFiUDP &ntpUDP) : timeClient(ntpUDP) {}

void TimeManager::begin() {
  timeClient.begin();
  timeClient.setTimeOffset(-4 * 3600); // Eastern Daylight Time
  updateTime();
}

void TimeManager::updateTime() {
  timeClient.update();
  int seconds = timeClient.getSeconds();
  updateInterval = (60 - seconds) * 1000;
  hours = timeClient.getHours();
  minutes = timeClient.getMinutes();

  digits[0] = hours / 10;
  digits[1] = hours % 10;
  digits[2] = minutes / 10;
  digits[3] = minutes % 10;
}

bool TimeManager::timeUpdateDue(unsigned long currentMillis) {
  if (currentMillis - previousMillis >= updateInterval) {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

int* TimeManager::getTimeDigits() {
  return digits;
}
