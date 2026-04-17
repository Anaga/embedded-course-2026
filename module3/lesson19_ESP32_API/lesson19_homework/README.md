Lesson 17 Homework - REST APIs and JSON on ESP32
=================================================

All infrastructure (WiFi, NTP, HTTP fetch, JSON parsing, LED) is
pre-written. Your task is to implement three features inside
src/main.cpp.

Setup
-----
1. Open include/config.h and set SSID / PASSWORD.
2. Build and flash. The demo should already print prices to Serial.
3. Implement the three TODOs below one at a time.

TODO 1 - printTop3Cheapest()
------------------------------
Find the three cheapest hours in the price array and print them.

Expected output (prices are examples):
    Top 3 cheapest hours:
      03:00   41.10 EUR/MWh
      04:00   45.80 EUR/MWh
      02:00   52.30 EUR/MWh

Hint: scan the array three times, keeping track of which indices you
have already reported. Or sort a local copy of the array.

TODO 2 - getPriceCategory()
-----------------------------
Return a string label for the price:
    price < 50.0           -> "cheap"
    price >= 50.0 < 100.0  -> "normal"
    price >= 100.0         -> "expensive"

The function is already called in printSummary(). Once implemented,
Serial output will show:
    Current :   85.23 EUR/MWh  [normal]

TODO 3 - loop() periodic refresh
----------------------------------
Call refreshData() once per hour using millis() without blocking.

Requirements:
  - Declare a static uint32_t to track the last refresh time.
  - Use the subtraction pattern: millis() - lastRefresh >= REFRESH_INTERVAL_MS
  - Do NOT use delay() for the long wait.

REFRESH_INTERVAL_MS is defined in include/config.h (default: 3600000).
You can reduce it temporarily (e.g. to 10000 ms) for testing.

File layout
-----------
    platformio.ini              (do not modify)
    include/
        config.h                Set SSID and PASSWORD here
        wifi_helper.h           (provided, do not modify)
        elering.h               (provided, do not modify)
        led.h                   (provided, do not modify)
    src/
        wifi_helper.cpp         (provided, do not modify)
        elering.cpp             (provided, do not modify)
        led.cpp                 (provided, do not modify)
        main.cpp                -- YOUR WORK IS HERE --
