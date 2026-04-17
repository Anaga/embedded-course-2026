#pragma once
#include <Arduino.h>
#include <stdint.h>

// Connect to WiFi using credentials from config.h.
// Blocks until connected.
void connectWiFi();

// Synchronize the ESP32 clock via NTP.
// Blocks until the time is valid.
void syncNTP();

// Return the current Unix UTC timestamp in seconds.
time_t nowUnix();
