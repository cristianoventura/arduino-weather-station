# Arduino Weather Station

A small Arduino sketch that fetches the current weather from [Open-Meteo](https://open-meteo.com) over WiFi and displays it on a 16x2 I2C LCD.

<img width="500" alt="weather-station" src="https://github.com/user-attachments/assets/b5ba2679-e35e-4414-b165-f0e927e05aa7" />


## Hardware

| Component                       | Notes                                                |
| ------------------------------- | ---------------------------------------------------- |
| Arduino UNO R4 WiFi             | Required — the sketch uses the `WiFiS3` library     |
| 16x2 character LCD with I2C backpack (PCF8574) | Default address `0x27` (some modules use `0x3F`) |
| 4 jumper wires                  | Female–male recommended for direct board-to-LCD     |
| USB-C cable                     | Power + flashing                                     |

## Wiring

The LCD's I2C backpack has four pins: `GND`, `VCC`, `SDA`, `SCL`. Connect them to the Arduino as follows:

| LCD pin | Arduino UNO R4 WiFi pin |
| ------- | ----------------------- |
| `GND`   | `GND`                   |
| `VCC`   | `5V`                    |
| `SDA`   | `SDA` (also labeled `A4`) |
| `SCL`   | `SCL` (also labeled `A5`) |

No external resistors are needed — the I2C backpack has its own pull-ups, and the UNO R4 runs the bus at 3.3 V logic which the PCF8574 tolerates fine on a 5V supply.

<img width="600" alt="circuit_image" src="https://github.com/user-attachments/assets/f9f6e7a3-f49e-46d5-aadb-96a635d847ac" />

## Required libraries

Install these from **Tools > Manage Libraries** in the Arduino IDE:

- `LiquidCrystal_I2C`
- `ArduinoHttpClient`
- `Arduino_JSON`

`WiFiS3` and `Wire` ship with the Arduino UNO R4 board package — install it from **Tools > Board > Boards Manager** by searching for "Arduino UNO R4".

## Configuration (`config.h`)

All tweakable values live in [`config.h`](config.h). Change your WiFi credentials and the coordinates before uploading the code.

```c
// WiFi credentials
#define WIFI_SSID     ""
#define WIFI_PASSWORD ""

// Weather API endpoint (no need to change)
#define WEATHER_HOST  "api.open-meteo.com"
#define WEATHER_PORT  80

// Location to fetch weather for - defaults to Toronto
#define LATITUDE   43.6313973
#define LONGITUDE  -79.3919476

// How often to re-fetch the weather - default: every hour
#define FETCH_INTERVAL_MS 3600000UL

// LCD I2C address and dimensions. Try 0x3F if 0x27 shows nothing.
#define LCD_ADDR  0x27
#define LCD_COLS  16
#define LCD_ROWS  2
```

### Variable reference

| Variable             | What to set it to                                                                  |
| -------------------- | ---------------------------------------------------------------------------------- |
| `WIFI_SSID`          | Your 2.4 GHz network name. The UNO R4's radio does not support 5 GHz.              |
| `WIFI_PASSWORD`      | Your WiFi password. Up to 63 characters.                                           |
| `LATITUDE`           | Decimal latitude for your location.                             |
| `LONGITUDE`          | Decimal longitude for your location.                             |
| `FETCH_INTERVAL_MS`  | Milliseconds between weather refreshes. `3600000` = 1 hour.                        |
| `LCD_ADDR`           | I2C address of your LCD backpack. Most are `0x27`; some are `0x3F`.                |
| `LCD_COLS` / `LCD_ROWS` | LCD dimensions. Change if you swap to a different module.                            |

### iPhone hotspot

If you're using an iPhone Personal Hotspot as the WiFi source:

1. Settings > Personal Hotspot > **Maximize Compatibility = ON** (forces 2.4 GHz).
2. Rename the hotspot to an **ASCII-only name** (Settings > General > About > Name). Curly apostrophes in names like `Someone's iPhone` will not match.
3. Keep the Personal Hotspot settings screen **open** on the iPhone until the Arduino connects — iOS sleeps the radio otherwise.

## Flashing

1. Plug the UNO R4 WiFi into your computer.
2. Select **Tools > Board > Arduino UNO R4 WiFi** and the matching serial port.
3. Open `WeatherStation.ino` in the Arduino IDE and click **Upload**.
4. Open the Serial Monitor at **9600 baud** to watch the connection progress.

On boot the LCD shows `Connecting...`. Once WiFi is up and the first fetch succeeds, you'll see a weather icon, the current temperature, and a short description.
