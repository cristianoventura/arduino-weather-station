#include "WifiManager.h"
#include "Config.h"
#include <WiFiS3.h>

bool connectWiFi() {
  for (int attempt = 1; attempt <= 3; attempt++) {
    delay(1000);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long start = millis();
    while (!isWiFiConnected() && millis() - start < 15000) {
      delay(500);
    }

    if (isWiFiConnected()) return true;

    WiFi.end();
    delay(2000);
  }
  return false;
}

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED && WiFi.localIP()[0] != 0;
}
