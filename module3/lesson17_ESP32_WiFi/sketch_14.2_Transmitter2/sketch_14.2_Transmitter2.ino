#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <stdio.h>
#include <string.h>

uint8_t peerMac[6];

void macFromStr(const char* s, uint8_t* m) {
  sscanf(s, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
         &m[0], &m[1], &m[2], &m[3], &m[4], &m[5]);
}

void setup() {
  Serial.begin(115200);
  delay(300);

  WiFi.mode(WIFI_STA);

<<<<<<< HEAD
  // Fixing the channel ESP-NOW (очень помогает)
=======
  // фиксируем канал для ESP-NOW (очень помогает)
>>>>>>> 4cb65eecf0767e5f6b7c7bd3e223732c684506fb
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init FAILED");
    return;
  }

  macFromStr("68:FE:71:FD:33:44", peerMac);  // <-- вставьте MAC Receiver

  esp_now_peer_info_t p = {};
  memcpy(p.peer_addr, peerMac, 6);
  p.channel = 1;         // фиксированный канал
  p.encrypt = false;

  if (esp_now_add_peer(&p) != ESP_OK) {
    Serial.println("Add peer FAILED");
    return;
  }

  Serial.println("Transmitter ready.");
}

void loop() {
<<<<<<< HEAD
  const char* msg = "Hello";
  esp_err_t r = esp_now_send(peerMac, (const uint8_t*)msg, strlen(msg)); // string lenght
=======
  const char* msg = "FRIDAY TIME!!";
  esp_err_t r = esp_now_send(peerMac, (const uint8_t*)msg, strlen(msg));
>>>>>>> 4cb65eecf0767e5f6b7c7bd3e223732c684506fb

  if (r == ESP_OK) Serial.println("Sent: Hello");
  else Serial.printf("Send FAILED: %d\n", r);

  delay(1000);
}
