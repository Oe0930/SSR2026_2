

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "esp_bt_device.h"

BluetoothSerial SerialBT;

void setup() {
    Serial.begin(115200);

    if (!SerialBT.begin("ESP32")) {
        Serial.println("Bluetooth init failed");
        while (1);
    }

    const uint8_t *mac = esp_bt_dev_get_address();

    Serial.printf("BT MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  mac[0], mac[1], mac[2],
                  mac[3], mac[4], mac[5]);
}

void loop() {}

// EC:E3:34:D2:AB:6A // ESP32 Oe
// 78:42:1c:2d:10:c6 // PS4
// 78:42:1C:2D:3B:AA // ESP32 Yago