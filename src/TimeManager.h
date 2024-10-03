#ifndef TimeManager_h
#define TimeManager_h

#include <NTPClient.h>
#include <WiFiUdp.h>

class TimeManager {
  private:
    NTPClient timeClient;
    unsigned long previousMillis = 0;
    long updateInterval = 60000;
    int digits[4];
    int hours;
    int minutes;

  public:
    TimeManager(WiFiUDP &ntpUDP);
    void begin();
    void updateTime();
    bool timeUpdateDue(unsigned long currentMillis);
    int* getTimeDigits();
};

#endif
