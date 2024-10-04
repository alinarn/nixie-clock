#include <NTPClient.h>
#include <WiFiNINA.h> 
#include <WiFiUdp.h>
#include "config/bcd.h"
#include "config/config.h"
#include "src/Bulb.h"
#include "src/Display.h"
#include "src/TimeManager.h"

WiFiUDP ntpUDP;

unsigned long previousOnMillis = 0;
unsigned long previousOffMillis = 0;
unsigned long lastCycleTime = 0;
short bulbIndex = 0;
bool bulbState = LOW;

TimeManager timeManager(ntpUDP);
Display display;

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  timeManager.begin();
  displayTime();
}

void loop() {
  unsigned long currentMillis = millis();

  if (timeManager.timeUpdateDue(currentMillis)) {
    timeManager.updateTime();
    displayTime();
    Serial.println("Time updated");
  }

  if (currentMillis - lastCycleTime >= CYCLE_INTERVAL) {
    display.cycleDigits();
    lastCycleTime = currentMillis;
  }

  if (!bulbState && currentMillis - previousOnMillis >= ON_INTERVAL) {
    previousOnMillis = currentMillis;
    display.turnOnBulb(bulbIndex);
    bulbState = HIGH;
  }

  if (bulbState && currentMillis - previousOffMillis >= OFF_INTERVAL) {
    previousOffMillis = currentMillis;
    display.turnOffBulb(bulbIndex);
    bulbState = LOW;
    bulbIndex = (bulbIndex + 1) % 4;
  }
}

void displayTime() {
  int* digits = timeManager.getTimeDigits();
  display.displayNumber(digits);
}

void connectToWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(SSID);
    WiFi.begin(SSID, PASS);
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}
