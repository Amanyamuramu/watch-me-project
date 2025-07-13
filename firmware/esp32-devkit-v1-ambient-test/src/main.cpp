#include <Arduino.h>
#include <Ambient.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "main.h"

WiFiClient client;
Ambient ambient;

#define CDS_PIN 34
#define LED_PIN_RED 2 // 内蔵LEDはGPIO2に接続
const float VOLTAGE_THRESHOLD = 1.85; // 電圧のしきい値

void setup() {
  Serial.begin(115200);
  //wifi設定
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Ambient初期化
  ambient.begin(channelId, writeKey, &client);

  //pin設定
  pinMode(CDS_PIN, INPUT);
  pinMode(LED_PIN_RED, OUTPUT); // 内蔵LEDを出力モードに設定
  digitalWrite(LED_PIN_RED, LOW); // 内蔵LEDを消灯
}

void loop() {
  int analog_data = analogRead(CDS_PIN); // Read from D4 pin
  float voltage = float(analog_data) * (3.3 / 4095.0); // Convert ADC value to voltage
  int inRoom = 0; //0:outside, 1:inside
  Serial.print(voltage);
  Serial.println(" V");
  if(voltage < VOLTAGE_THRESHOLD) {
    inRoom = 0;
  } else {
    inRoom = 1;
  }

  // 送信ambient
  ambient.set(1, voltage);
  ambient.set(2, inRoom);
  if (ambient.send()) {
    Serial.println("Data sent to Ambient!");
  } else {
    Serial.println("Failed to send data.");
  }
  int send_minuite = 5; // 5分ごとに送信
  delay(send_minuite * 60 * 1000); // 5分待機
  // delay(10000);// 10秒待機、実際には5分ごとに送信

  /*
  float tempature_esp32 = temperatureRead();
  Serial.print("Temperature: ");
  Serial.println(tempature_esp32);
  */
}