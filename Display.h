#ifndef DISPLAY_H
#define DISPLAY_H

#include "WeatherApi.h"

void initDisplay();
void showMessage(const char* line1, const char* line2 = nullptr);
void showWeather(const WeatherData& data);

#endif
