#include <WiFi.h>
#include <esp_now.h>
#include "Freenove_WS2812_Lib_for_ESP32.h"

//#define LEDS_COUNT  8
//#define LEDS_PIN	2
//#define CHANNEL		0

//Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

//uint8_t m_color[5][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 0} };
//int delayval = 100;

typedef struct struct_message {
    char a[32];
    int b;
    float c;
    bool d;
    int e;
} struct_message;

// Create a struct_message called myData
struct_message myData;


/*void onRx(const esp_now_recv_info_t* info, const uint8_t* data, int len) {
  Serial.printf("From %02X:%02X:%02X:%02X:%02X:%02X | ",
                info->src_addr[0], info->src_addr[1], info->src_addr[2],
                info->src_addr[3], info->src_addr[4], info->src_addr[5]);

  Serial.print("Msg: ");
  for (int i = 0; i < len; i++) Serial.print((char)data[i]);
  Serial.println();
}*/


void OnDataRecv(const esp_now_recv_info_t* info, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("Bool: ");
  Serial.println(myData.d);
  Serial.print("Sent value: ");
  Serial.println(myData.e);
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
  esp_now_register_recv_cb(OnDataRecv);
  //esp_now_register_recv_cb(onRx);
  Serial.println("Receiver ready.");

  //strip.begin();
	//strip.setBrightness(5);	
}

void loop() {
  //esp_now_register_recv_cb(OnDataRecv);
  Serial.print(myData.b);
  //Serial.print(myData.e);
  //Serial.print("My MAC: ");
  //Serial.println(WiFi.macAddress());
  
  //esp_now_register_recv_cb(onRx);
  Serial.println("Receiver ready.");
  /*for (int i = 0; i < LEDS_COUNT; i++) {
      esp_now_register_recv_cb(OnDataRecv);
			strip.setLedColorData(i, 255, 0, 0);
			strip.show();
			delay(myData.e);
      strip.setLedColorData(i, 0, 0, 0);
      strip.show();
		}*/
  delay(2000);
}
