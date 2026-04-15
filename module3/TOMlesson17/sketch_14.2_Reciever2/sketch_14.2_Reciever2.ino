#include <WiFi.h>
#include <esp_now.h>

void onRx(const esp_now_recv_info_t* info, const uint8_t* data, int len) {
  Serial.printf("From %02X:%02X:%02X:%02X:%02X:%02X | ",
                info->src_addr[0], info->src_addr[1], info->src_addr[2],
                info->src_addr[3], info->src_addr[4], info->src_addr[5]);

  Serial.print("Msg: ");
  for (int i = 0; i < len; i++) Serial.print((char)data[i]);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(300);

  WiFi.mode(WIFI_STA);
  Serial.print("My MAC: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init FAILED");
    return;
  }

  esp_now_register_recv_cb(onRx);
  Serial.println("Receiver ready.");
}

void loop() {
Serial.print("My MAC: ");
Serial.println(WiFi.macAddress());
esp_now_register_recv_cb(onRx);

delay(2000);
}
