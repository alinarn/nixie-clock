#include <NTPClient.h>
#include <WiFiNINA.h> 
#include <WiFiUdp.h>
#include "config/bcd.h"
#include "config/config.h"
#include "secrets.h"
#include "src/Bulb.h"
#include "src/Display.h"
#include "src/TimeManager.h"

const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;

WiFiUDP ntpUDP;

unsigned long previousOnMillis = 0;
unsigned long previousOffMillis = 0;
unsigned long lastCycleTime = 0;
const long onInterval = 1;
const long offInterval = 3;
const long cycleInterval = 3660000; // 1 hour 1 min in milliseconds
int bulbIndex = 0;
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

  if (currentMillis - lastCycleTime >= cycleInterval) {
    display.cycleDigits();
    lastCycleTime = currentMillis;
  }

  if (!bulbState && currentMillis - previousOnMillis >= onInterval) {
    previousOnMillis = currentMillis;
    display.turnOnBulb(bulbIndex);
    bulbState = HIGH;
  }

  if (bulbState && currentMillis - previousOffMillis >= offInterval) {
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
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}
