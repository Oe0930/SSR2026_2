#pragma once

// サーボ
const uint8_t ETC_SERVO_PIN1 = 16;
const uint8_t ETC_SERVO_PIN2 = 17;
const uint8_t LIFT_SERVO_PIN = 18;
const uint8_t BACK_SERVO_PIN = 19;

// リミットスイッチ
const uint8_t LIMITSWITCH_PIN1 = 22;
const uint8_t LIMITSWITCH_PIN2 = 23;

// 駆動DC

// 0 : 後輪 
// 1 : 右前輪 
// 2 : 左前輪 
const uint8_t WHEEL_PWM_PINS[] = { 32, 25, 27 };
const uint8_t WHEEL_DIR_PINS[] = { 33, 26, 14 };
const uint8_t WHEEL_PWM_CHANNELS[] = { 3, 4, 5 };