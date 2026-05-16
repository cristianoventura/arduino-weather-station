#include "WeatherApi.h"
#include "Config.h"
#include <WiFiS3.h>
#include <ArduinoHttpClient.h>
#include <Arduino_JSON.h>

static WiFiClient wifi;
static HttpClient client = HttpClient(wifi, WEATHER_HOST, WEATHER_PORT);

WeatherData fetchWeather() {
  WeatherData result = {0, 0, 0, 1, false};

  // build path with current coordinates
  char path[200];
  snprintf(path, sizeof(path),
    "/v1/forecast?latitude=%.6f&longitude=%.6f&current=temperature_2m,weather_code,wind_speed_10m,is_day",
    LATITUDE, LONGITUDE);

  Serial.println("Fetching weather...");

  client.stop();
  client.get(path);
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  if (statusCode != 200) return result;

  JSONVar data = JSON.parse(response);
  if (JSON.typeof(data) == "undefined") return result;

  result.temperature = (double) data["current"]["temperature_2m"];
  result.weatherCode = (int) data["current"]["weather_code"];
  result.windSpeed = (double) data["current"]["wind_speed_10m"];
  result.isDay = (int) data["current"]["is_day"];
  result.valid = true;
  return result;
}
