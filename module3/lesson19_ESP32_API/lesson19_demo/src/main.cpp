#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "wifi_helper.h"
#include "elering.h"
#include "led.h"
#include <WiFi.h>

// ---------------------------------------------------------------------------
// printSummary
// Print the price summary to Serial in a readable format.
// ---------------------------------------------------------------------------
static void printSummary(const PriceSummary& s) {
    Serial.println("-----------------------------");
    if (s.curPrice >= 0.0f) {
        Serial.printf("Current : %7.2f EUR/MWh\n", s.curPrice);
    } else {
        Serial.println("Current : (not in today's data)");
    }
    Serial.printf("Min     : %7.2f EUR/MWh  (hour %u)\n",
                  s.minPrice, s.minHour);
    Serial.printf("Max     : %7.2f EUR/MWh  (hour %u)\n",
                  s.maxPrice, s.maxHour);
    Serial.println("-----------------------------");
}

// ---------------------------------------------------------------------------
// refreshData
// Fetch today's prices, print the summary, and update the LED.
// ---------------------------------------------------------------------------
static void refreshData() {
    Serial.println("Fetching Elering price data...");

    time_t now = nowUnix();
    PriceSummary summary;

    if (!fetchAndAnalyze(now, summary)) {
        Serial.println("ERROR: Could not fetch or parse price data.");
        ledOff();
        return;
    }

    printSummary(summary);

    if (summary.curPrice >= 0.0f) {
        showPrice(summary.curPrice, summary.minPrice, summary.maxPrice);
    } else {
        // Current hour not yet published -- show a dim blue
        ledOff();
    }
}

// ---------------------------------------------------------------------------
// setup
// ---------------------------------------------------------------------------
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Lesson 17 - REST APIs and JSON on ESP32");

    initLed();
    connectWiFi();
    syncNTP();

    refreshData();
}

// ---------------------------------------------------------------------------
// loop
// ---------------------------------------------------------------------------
void loop() {
    static uint32_t lastRefresh = 0UL;
    String currentSSID = WiFi.SSID();
<<<<<<< HEAD
=======

    Serial.println("Checking WiFi connection...");
    Serial.println("Current SSID: " + currentSSID);

>>>>>>> 6cbc59c05515da681a0f4b57d62a5a2118dfa7ca

    // Serial.printf
    if (millis() - lastRefresh >= REFRESH_INTERVAL_MS) {
        lastRefresh = millis();
        refreshData();
    }
}
