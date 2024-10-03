#include <NTPClient.h>
#include <WiFiNINA.h> 
#include <WiFiUdp.h>
#include "bcd.h"
#include "config.h"
#include "secrets.h"
#include "Bulb.h"
#include "Display.h"
#include "TimeManager.h"

const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;

WiFiUDP ntpUDP;

unsigned long previousOnMillis = 0;
unsigned long previousOffMillis = 0;
const long onInterval = 1;
const long offInterval = 3;
int bulbIndex = 0;
bool bulbState = LOW;

TimeManager timeManager(ntpUDP);
Display display;

void setup() {
  Serial.begin(115200);
  while ( WiFi.status() != WL_CONNECTED ) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    delay(1000);
  }
  Serial.println("Connected to WiFi");
  timeManager.begin();
  int* digits = timeManager.getTimeDigits();
  display.displayNumber(digits);
}

void loop() {
  unsigned long currentMillis = millis();

  if (timeManager.timeUpdateDue(currentMillis)) {
    timeManager.updateTime();
    int* digits = timeManager.getTimeDigits();
    display.displayNumber(digits);
    Serial.println("Time updated");
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
