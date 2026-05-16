#include "display.h"
#include "config.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

static LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

static byte sunIcon[8] = {
  B00100, B10101, B01110, B11111, B01110, B10101, B00100, B00000
};

static byte cloudIcon[8] = {
  B00000, B00110, B01111, B11111, B11111, B00000, B00000, B00000
};

static byte rainIcon[8] = {
  B01110, B11111, B11111, B00000, B01010, B10101, B01010, B10101
};

static byte snowIcon[8] = {
  B00000, B10101, B01110, B11111, B01110, B10101, B00000, B00000
};

static byte stormIcon[8] = {
  B01110, B11111, B11111, B00100, B01000, B11110, B00100, B01000
};

static byte fogIcon[8] = {
  B00000, B11111, B00000, B11111, B00000, B11111, B00000, B11111
};

static byte windIcon[8] = {
  B00000, B11100, B00010, B11110, B00001, B11110, B00000, B00000
};

static byte moonIcon[8] = {
  B00110, B01100, B11100, B11000, B11000, B11100, B01100, B00110
};

static int pickIcon(int code, double wind, int isDay) {
  if (wind >= 30.0) return 6;              // windy (km/h)
  if (code == 0) return isDay ? 0 : 7;     // clear: sun by day, moon by night
  if (code >= 1 && code <= 3) return 1;    // mostly clear / partly cloudy / overcast
  if (code == 45 || code == 48) return 5;  // fog
  if (code >= 51 && code <= 67) return 2;  // drizzle / rain
  if (code >= 71 && code <= 77) return 3;  // snow
  if (code >= 80 && code <= 82) return 2;  // rain showers
  if (code >= 85 && code <= 86) return 3;  // snow showers
  if (code >= 95) return 4;                // thunderstorm
  return 1;                                // fallback: cloud
}

static const char* describe(int code) {
  if (code == 0) return "Clear";
  if (code == 1) return "Mostly clear";
  if (code == 2) return "Partly cloudy";
  if (code == 3) return "Overcast";
  if (code == 45 || code == 48) return "Foggy";
  if (code >= 51 && code <= 55) return "Drizzle";
  if (code >= 61 && code <= 65) return "Rainy";
  if (code >= 71 && code <= 75) return "Snowy";
  if (code >= 80 && code <= 82) return "Showers";
  if (code >= 95) return "Storm";
  return "Unknown";
}

void initDisplay() {
  lcd.init();
  lcd.backlight();

  lcd.createChar(0, sunIcon);
  lcd.createChar(1, cloudIcon);
  lcd.createChar(2, rainIcon);
  lcd.createChar(3, snowIcon);
  lcd.createChar(4, stormIcon);
  lcd.createChar(5, fogIcon);
  lcd.createChar(6, windIcon);
  lcd.createChar(7, moonIcon);

  lcd.setCursor(0, 0);
}

void showMessage(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  if (line2) {
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
}

void showWeather(const WeatherData& data) {
  int iconSlot = pickIcon(data.weatherCode, data.windSpeed, data.isDay);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(byte(iconSlot));
  lcd.print(" ");
  lcd.print(data.temperature, 1);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print(describe(data.weatherCode));
}
