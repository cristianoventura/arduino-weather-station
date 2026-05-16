#include "Config.h"
#include "WifiManager.h"
#include "WeatherApi.h"
#include "Display.h"

unsigned long lastFetch = 0;

void setup() {
  Serial.begin(9600);
  delay(2000);

  initDisplay();
  showMessage("Connecting...");

  if (!connectWiFi()) {
    showMessage("WiFi failed");
    while (true);
  }

  WeatherData data = fetchWeather();
  if (data.valid) showWeather(data);
  lastFetch = millis();
}

void loop() {
  if (!isWiFiConnected()) {
    showMessage("Reconnecting...");
    connectWiFi();
  }

  if (millis() - lastFetch >= FETCH_INTERVAL_MS) {
    lastFetch = millis();
    WeatherData data = fetchWeather();
    if (data.valid) showWeather(data);
  }
}
