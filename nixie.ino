#include <NTPClient.h>
#include <WiFiNINA.h> 
#include <WiFiUdp.h>
#include "bcd.h"
#include "config.h"
#include "secrets.h"
#include "Bulb.h"
#include "Display.h"

const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

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

  int digits[4] = {1,2,3,4};
  display.displayNumber(digits);

  timeClient.begin();
  timeClient.setTimeOffset(-4 * 3600);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    display.turnOnBulb(i);
    delay(1000);
    display.turnOffBulb(i);
  }
}