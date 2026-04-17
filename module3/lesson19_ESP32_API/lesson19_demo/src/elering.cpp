#include "elering.h"
#include "config.h"

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include <stdio.h>

// ---------------------------------------------------------------------------
// buildUrl
// ---------------------------------------------------------------------------
String buildUrl(time_t now) {
    struct tm t;
    gmtime_r(&now, &t);  // Convert to UTC broken-down time

    char start[28];
    char end[28];

    snprintf(start, sizeof(start),
             "%04d-%02d-%02dT00:00:00Z",
             t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);

    snprintf(end, sizeof(end),
             "%04d-%02d-%02dT23:59:59Z",
             t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);

    String url = "https://dashboard.elering.ee/api/nps/price?start=";
    url += start;
    url += "&end=";
    url += end;

    Serial.println("URL: " + url);
    return url;
}

// ---------------------------------------------------------------------------
// fetchPrices
// ---------------------------------------------------------------------------
String fetchPrices(const String& url) {
    WiFiClientSecure client;
    client.setInsecure();  // Skip TLS certificate verification (demo only)

    HTTPClient http;
    http.begin(client, url);

    int code = http.GET();
    if (code == HTTP_CODE_OK) {
        String body = http.getString();
        http.end();
        return body;
    }

    Serial.printf("HTTP error: %d\n", code);
    http.end();
    return "";
}

// ---------------------------------------------------------------------------
// parsePriceArray
// ---------------------------------------------------------------------------
uint8_t parsePriceArray(const String& body, PriceEntry* out) {
    JsonDocument doc;

    DeserializationError err = deserializeJson(doc, body);
    if (err) {
        Serial.print("JSON parse error: ");
        Serial.println(err.c_str());
        return 0u;
    }

    if (!doc["success"].as<bool>()) {
        Serial.println("API returned success=false");
        return 0u;
    }

    JsonArray arr = doc["data"]["ee"].as<JsonArray>();
    uint8_t count = 0u;

    for (JsonObject obj : arr) {
        if (count >= MAX_ENTRIES) break;

        out[count].timestamp = obj["timestamp"].as<uint32_t>();
        out[count].price     = obj["price"].as<float>();
        count++;
    }

    Serial.printf("Parsed %u price entries\n", count);
    return count;
}

// ---------------------------------------------------------------------------
// analyze
// ---------------------------------------------------------------------------
PriceSummary analyze(const PriceEntry* entries,
                     uint8_t count,
                     time_t  now) {
    PriceSummary r;
    r.minPrice = entries[0].price;
    r.maxPrice = entries[0].price;
    r.curPrice = -1.0f;
    r.minHour  = 0u;
    r.maxHour  = 0u;

    // Floor current time to the start of the current hour (UTC)
    time_t hourNow = (now / 3600) * 3600;

    for (uint8_t i = 0u; i < count; i++) {
        if (entries[i].price < r.minPrice) {
            r.minPrice = entries[i].price;
            r.minHour  = i;
        }
        if (entries[i].price > r.maxPrice) {
            r.maxPrice = entries[i].price;
            r.maxHour  = i;
        }
        if ((time_t)entries[i].timestamp == hourNow) {
            r.curPrice = entries[i].price;
        }
    }

    return r;
}

// ---------------------------------------------------------------------------
// fetchAndAnalyze
// ---------------------------------------------------------------------------
bool fetchAndAnalyze(time_t now, PriceSummary& result) {
    String url  = buildUrl(now);
    String body = fetchPrices(url);

    if (body.isEmpty()) {
        return false;
    }

    static PriceEntry entries[MAX_ENTRIES];
    uint8_t count = parsePriceArray(body, entries);

    if (count == 0u) {
        return false;
    }

    result = analyze(entries, count, now);
    return true;
}
