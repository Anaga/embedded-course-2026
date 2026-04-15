#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <stdio.h>
#include <string.h>

//const int potPin = 34; // ADC1_CH6
//int potValue = 0;

uint8_t peerMac[6];
//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
  int e;
} struct_message;

// Create a struct_message called myData
struct_message myData;


void macFromStr(const char* s, uint8_t* m) {
  sscanf(s, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
         &m[0], &m[1], &m[2], &m[3], &m[4], &m[5]);
}

void setup() {
  Serial.begin(115200);
  delay(300);

  WiFi.mode(WIFI_STA);

  // Fixing the channel ESP-NOW (очень помогает)
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init FAILED");
    return;
  }

  macFromStr("00:70:07:19:C3:60", peerMac);  // <-- insert MAC Receiver

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
  //const char* msg = "Hello world";
  strcpy(myData.a, "THIS IS A CHAR");
  myData.b = random(1,20);
  myData.c = 1.2;
  myData.d = false;
  //myData.e = analogRead(potPin);
  Serial.println(myData.a);
  Serial.println(myData.b);
  //Serial.println(myData.e);
  //esp_err_t r = esp_now_send(peerMac, (const uint8_t*)&msg, strlen(msg));
  esp_err_t r = esp_now_send(peerMac, (uint8_t*)&myData, sizeof(myData));
  if (r == ESP_OK) Serial.println("Data sent");
  else Serial.printf("Send FAILED: %d\n", r);
  //potValue = analogRead(potPin); // 0-4095
  //Serial.print(msg);
  //Serial.println(potValue);


  delay(5000);
}
