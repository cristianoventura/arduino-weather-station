#include "config.h"
#include "wifi_manager.h"
#include "weather_api.h"
#include "display.h"

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
