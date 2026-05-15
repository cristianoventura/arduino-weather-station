#ifndef WEATHER_API_H
#define WEATHER_API_H

struct WeatherData {
  double temperature;
  int weatherCode;
  double windSpeed;
  int isDay;
  bool valid;
};

WeatherData fetchWeather();

#endif
