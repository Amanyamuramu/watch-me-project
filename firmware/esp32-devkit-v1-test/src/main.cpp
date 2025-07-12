#include <Arduino.h>
#define CDS_PIN 4
#define LED_PIN_RED 2 // 内蔵LEDはGPIO2に接続

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    // Wait for Serial to be ready
    delay(100);
  }
  pinMode(CDS_PIN, INPUT);
  pinMode(LED_PIN_RED, OUTPUT); // 内蔵LEDを出力モードに設定
  digitalWrite(LED_PIN_RED, LOW); // 内蔵LEDを消灯
}

void loop() {
  int analog_data = analogRead(CDS_PIN); // Read from D4 pin
  float voltage = float(analog_data) * (3.3 / 4095.0); // Convert ADC value to voltage
  Serial.print(voltage);
  Serial.println(" V");
  delay(1000);

  /*
  float tempature_esp32 = temperatureRead();
  Serial.print("Temperature: ");
  Serial.println(tempature_esp32);
  */
}