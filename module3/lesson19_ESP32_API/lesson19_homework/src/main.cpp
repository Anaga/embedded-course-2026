#include <Arduino.h>

#include "config.h"
#include "wifi_helper.h"
#include "elering.h"
#include "led.h"

// ---------------------------------------------------------------------------
// TODO 2: Define price categories.
//
// Implement this function so it returns a string label for the given price:
//   price < 50.0           -> "cheap"
//   price >= 50.0 and < 100.0  -> "normal"
//   price >= 100.0         -> "expensive"
//
// The function must return a const char* from a small set of string literals.
// Do not use heap allocation (String class) here.
// ---------------------------------------------------------------------------
const char* getPriceCategory(float price) {
    // TODO: replace the line below with your implementation
    (void)price;
    return "unknown";
}

// ---------------------------------------------------------------------------
// TODO 1: Print the three cheapest hours of the day.
//
// Given the sorted (or unsorted) array of price entries and a count,
// find and print the three entries with the lowest price values.
//
// For each of the three cheapest hours print:
//   "  HH:00  XX.XX EUR/MWh"
//
// Hint: one approach is to scan the array three times. On each pass,
//       skip entries you have already selected (track used indices).
//       Another approach: sort a copy of the array by price.
//
// The function receives the raw entries array and the count of valid entries.
// You may add helper variables inside the function body.
// ---------------------------------------------------------------------------
void printTop3Cheapest(const PriceEntry* entries, uint8_t count) {
    Serial.println("Top 3 cheapest hours:");
    // TODO: implement the search and printing below.
    // Remove or replace this placeholder:
    (void)entries;
    (void)count;
    Serial.println("  (not implemented yet)");
}

// ---------------------------------------------------------------------------
// Pre-written: printSummary
// ---------------------------------------------------------------------------
static void printSummary(const PriceSummary& s,
                         const PriceEntry* entries,
                         uint8_t count) {
    Serial.println("-----------------------------");
    if (s.curPrice >= 0.0f) {
        Serial.printf("Current : %7.2f EUR/MWh  [%s]\n",
                      s.curPrice, getPriceCategory(s.curPrice));
    } else {
        Serial.println("Current : (not in today's data)");
    }
    Serial.printf("Min     : %7.2f EUR/MWh  (hour %u)\n",
                  s.minPrice, s.minHour);
    Serial.printf("Max     : %7.2f EUR/MWh  (hour %u)\n",
                  s.maxPrice, s.maxHour);
    Serial.println("-----------------------------");
    printTop3Cheapest(entries, count);
    Serial.println("-----------------------------");
}

// ---------------------------------------------------------------------------
// Pre-written: internal entry buffer (static so it is not on the stack)
// ---------------------------------------------------------------------------
static PriceEntry g_entries[MAX_ENTRIES];
static uint8_t    g_count = 0u;

// ---------------------------------------------------------------------------
// Pre-written: refreshData
// Fetches today's prices, analyzes them, and updates Serial + LED.
// ---------------------------------------------------------------------------
static void refreshData() {
    Serial.println("Fetching Elering price data...");

    time_t now = nowUnix();
    String url  = buildUrl(now);
    String body = fetchPrices(url);

    if (body.isEmpty()) {
        Serial.println("ERROR: Could not fetch price data.");
        ledOff();
        return;
    }

    g_count = parsePriceArray(body, g_entries);
    if (g_count == 0u) {
        Serial.println("ERROR: Could not parse price data.");
        ledOff();
        return;
    }

    PriceSummary summary = analyze(g_entries, g_count, now);
    printSummary(summary, g_entries, g_count);

    if (summary.curPrice >= 0.0f) {
        showPrice(summary.curPrice, summary.minPrice, summary.maxPrice);
    } else {
        ledOff();
    }
}

// ---------------------------------------------------------------------------
// setup
// ---------------------------------------------------------------------------
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Lesson 17 Homework");

    initLed();
    connectWiFi();
    syncNTP();

    refreshData();
}

// ---------------------------------------------------------------------------
// TODO 3: Implement periodic refresh using millis().
//
// The demo currently calls refreshData() once and never again.
// Your task: call refreshData() once per hour, WITHOUT using delay()
// for the long wait.
//
// Requirements:
//   - Use a static uint32_t variable to store the time of the last refresh.
//   - Compare millis() with the stored time using subtraction.
//   - Use REFRESH_INTERVAL_MS from config.h as the interval.
//   - Do not block loop() with a long delay().
//
// The first refresh already happens in setup(), so lastRefresh should be
// initialised to millis() (or 0 if you want an immediate second call).
// ---------------------------------------------------------------------------
void loop() {
    // TODO: implement timed refresh here.
    // Replace the line below:
    (void)0;
}
