#include "wifi_helper.h"
#include "config.h"

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

void connectWiFi() {
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Connected. IP: ");
    Serial.println(WiFi.localIP());
}

void syncNTP() {
    configTime(TZ_OFFSET, DST_OFFSET,
               "pool.ntp.org",
               "time.nist.gov");

    struct tm ti;
    Serial.print("NTP sync");

    while (!getLocalTime(&ti)) {
        delay(500);
        Serial.print(".");
    }

    Serial.printf("\nTime: %02d:%02d:%02d\n",
                  ti.tm_hour, ti.tm_min, ti.tm_sec);
}

time_t nowUnix() {
    time_t t;
    time(&t);
    return t;
}
