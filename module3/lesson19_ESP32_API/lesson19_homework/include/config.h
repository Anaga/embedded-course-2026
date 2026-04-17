#pragma once

// ------------------------------------------------------------
// WiFi credentials -- do not commit to a public repository
// ------------------------------------------------------------
static const char* SSID     = "YOUR_SSID";
static const char* PASSWORD = "YOUR_PASSWORD";

// ------------------------------------------------------------
// NTP
// ------------------------------------------------------------
// EET = UTC+2 = 7200 seconds. DST set to 0 for simplicity.
static const long TZ_OFFSET  = 7200L;
static const int  DST_OFFSET = 0;

// ------------------------------------------------------------
// Price data
// ------------------------------------------------------------
// Maximum number of hourly entries stored in memory.
// 24 hours + 1 spare entry.
static const uint8_t MAX_ENTRIES = 25u;

// ------------------------------------------------------------
// WS2812
// ------------------------------------------------------------
// Onboard RGB LED on the ESP32-C3 Super Mini.
static const uint8_t ONBOARD_LED_PIN = 8u;
static const uint8_t ONBOARD_LED_CNT = 1u;

// Brightness cap (0-255). Keeps USB current within budget.
static const uint8_t MAX_BRIGHTNESS  = 80u;

// ------------------------------------------------------------
// Timing
// ------------------------------------------------------------
// Refresh interval in milliseconds (1 hour).
static const uint32_t REFRESH_INTERVAL_MS = 3600000UL;
