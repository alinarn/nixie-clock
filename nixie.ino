#include <NTPClient.h>
#include <WiFiNINA.h> 
#include <WiFiUdp.h>
#include "bcd.h"
#include "config.h"
#include "secrets.h"
#include "Bulb.h"

const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;

Bulb bulbs[] = {
    {BULB1_POWER_PIN, BULB1_NUMBER_PINS},
    {BULB2_POWER_PIN, BULB2_NUMBER_PINS},
    {BULB3_POWER_PIN, BULB3_NUMBER_PINS},
    {BULB4_POWER_PIN, BULB4_NUMBER_PINS}
};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  Serial.begin(115200);
  while ( WiFi.status() != WL_CONNECTED ) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    delay(1000);
  }

  Serial.println("Connected to WiFi");

  timeClient.begin();
  timeClient.setTimeOffset(-4 * 3600);
}

void loop() {
  for (int digit = 0; digit <= 9; digit++) {
    for (int i = 0; i < 4; i++) {
      bulbs[i].showDigit(digit);
      bulbs[i].turnOn();
      delay(1000);
      bulbs[i].turnOff();
      delay(1000);
    }
  }
}