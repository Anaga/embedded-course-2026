Lesson 17 Demo - REST APIs and JSON on ESP32
============================================

Fetches live Nord Pool electricity prices for Estonia from the
Elering Dashboard API, parses the JSON response with ArduinoJson,
and displays the current price as a green-to-red color on the
onboard WS2812 LED.

Hardware
--------
- ESP32-C3 Super Mini (lolin_c3_mini)
- Onboard WS2812 LED on GPIO 8

Dependencies (managed by PlatformIO)
--------------------------------------
- bblanchon/ArduinoJson ^7.0.0
- adafruit/Adafruit NeoPixel ^1.12.3

Mac COM port Config

Auto-detected: /dev/cu.usbmodem1301
Uploading .pio/build/lolin_c3_mini/firmware.bin
esptool.py v4.11.0
Serial port /dev/cu.usbmodem1301
Connecting...

Run

  git config --global user.email "bobyrev.bob@gmail.com"
  git config --global user.name "Aleksandr Bobyrev"

to set your account's default identity.

Setup
-----
1. Open include/config.h.
2. Set SSID and PASSWORD to match your network.
3. Build and flash with PlatformIO.
4. Open the Serial Monitor at 115200 baud.

Expected Serial output
-----------------------
    Connecting to WiFi........
    Connected. IP: 192.168.1.x
    NTP sync.
    Time: 14:05:32
    Fetching Elering price data...
    URL: https://dashboard.elering.ee/api/nps/price?start=2026-04-17T00:00:00Z&end=2026-04-17T23:59:59Z
    Parsed 24 price entries
    -----------------------------
    Current :   85.23 EUR/MWh
    Min     :   41.10 EUR/MWh  (hour 3)
    Max     :  198.70 EUR/MWh  (hour 19)
    -----------------------------

LED color
---------
    Green  -> current price is near today's minimum
    Yellow -> current price is near the middle of today's range
    Red    -> current price is near today's maximum

The display refreshes once per hour.

API reference
-------------
    Endpoint : GET https://dashboard.elering.ee/api/nps/price
    Params   : start, end  (ISO 8601 datetime, e.g. 2026-04-17T00:00:00Z)
    Price    : EUR/MWh  (divide by 1000 for EUR/kWh)
    Countries: ee, fi, lv, lt

Notes
-----
- WiFiClientSecure uses setInsecure() to skip TLS certificate
  verification. This is acceptable for a classroom demo but should
  not be used in production code.

- Timestamps in the API response are Unix UTC values. The clock on
  the ESP32 is also kept in UTC after NTP sync. The current-hour
  match uses integer floor division: (now / 3600) * 3600.

- The configTime() call uses UTC+2 (EET) for display only.
  All timestamp comparisons use UTC.

File layout
-----------
    platformio.ini
    include/
        config.h          WiFi credentials and constants
        wifi_helper.h     connectWiFi(), syncNTP(), nowUnix()
        elering.h         PriceEntry, PriceSummary, API functions
        led.h             initLed(), showPrice(), ledOff()
    src/
        wifi_helper.cpp
        elering.cpp
        led.cpp
        main.cpp
