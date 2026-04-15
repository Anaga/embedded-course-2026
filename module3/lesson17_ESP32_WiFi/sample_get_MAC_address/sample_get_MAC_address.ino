#include <WiFi.h>     // WiFi библиотека
//#include <esp_wifi.h>

void setup() {
  Serial.begin(115200);  // Serial
  delay(1000);           // Pause

  WiFi.mode(WIFI_STA);   // Important: WIFI - UP
  delay(100);            // delay
  const char* ssid = "Gamma Intelligence Training";
  const char* password = "10008218";


  //WiFi.begin(ssid, password);


  Serial.println("ESP32 MAC address:"); // заголовок
  Serial.println(WiFi.macAddress());    // Print the MAC
  Serial.println("Wi-Fi Connection Strength:"); // заголовок
  Serial.println(WiFi.RSSI());    // Wi-Fi Connection Strength
  Serial.println("IP Address:"); // заголовок
  Serial.println(WiFi.RSSI());    // Wi-Fi Connection Strength  
  Serial.println("Status:"); // заголовок
  Serial.println(WiFi.status());    // Wi-Fi Connection Strength  


  // Change ESP32 Mac Address
  // https://randomnerdtutorials.com/get-change-esp32-esp8266-mac-address-arduino/
  //esp_err_t err = esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);
  //if (err == ESP_OK) {
  //  Serial.println("Success changing Mac Address");
  //}
}

void loop() {
Serial.println("ESP32 MAC address:"); // заголовок
Serial.println(WiFi.macAddress());    // Print the MAC
Serial.println("Wi-Fi Connection Strength:"); // заголовок
Serial.println(WiFi.RSSI());    // Wi-Fi Connection Strength
Serial.println("IP Address:"); // заголовок
Serial.println(WiFi.localIP());    // Wi-Fi Connection Strength  
Serial.println("Status:"); // заголовок
Serial.println(WiFi.status());    // Wi-Fi Connection Strength  
delay(10000); 
}
  