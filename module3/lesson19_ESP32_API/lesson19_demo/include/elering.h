#pragma once
#include <Arduino.h>
#include <stdint.h>
#include <time.h>
#include "config.h"

// One hourly price record from the Elering API.
struct PriceEntry {
    uint32_t timestamp;  // Unix UTC timestamp (seconds)
    float    price;      // Price in EUR/MWh
};

// Summary computed from one day of price data.
struct PriceSummary {
    float   minPrice;   // Lowest price of the day
    float   maxPrice;   // Highest price of the day
    float   curPrice;   // Price for the current hour (-1 if not found)
    uint8_t minHour;    // Array index of the cheapest hour
    uint8_t maxHour;    // Array index of the most expensive hour
};

// Build the Elering API URL for the current UTC day.
// now: current Unix UTC timestamp.
// Returns a String of the form:
//   https://dashboard.elering.ee/api/nps/price?start=...&end=...
String buildUrl(time_t now);

// Perform an HTTPS GET request and return the response body.
// Returns an empty String on failure.
String fetchPrices(const String& url);

// Parse the "ee" (Estonia) price array from a JSON response body.
// Fills out[0..n-1] and returns the number of entries written.
uint8_t parsePriceArray(const String& body, PriceEntry* out);

// Scan the entries array and return min, max, and current-hour price.
PriceSummary analyze(const PriceEntry* entries,
                     uint8_t count,
                     time_t  now);

// Convenience wrapper: fetch + parse + analyze for the current day.
// Returns false if the fetch or parse failed.
bool fetchAndAnalyze(time_t now, PriceSummary& result);
