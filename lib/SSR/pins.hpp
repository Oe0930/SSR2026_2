#pragma once

// サーボ
const uint8_t ETC_SERVO_PIN1 = 32;
const uint8_t ETC_SERVO_PIN2 = 34;
const uint8_t LIFT_SERVO_PIN = 27;
const uint8_t BACK_SERVO_PIN = 13;

// リミットスイッチ
//const uint8_t LIMITSWITCH_PIN1 = 22;
//const uint8_t LIMITSWITCH_PIN2 = 23;

// 駆動DC

// 0 : 後輪 
// 1 : 右前輪 
// 2 : 左前輪 
const uint8_t WHEEL_PWM_PINS[] = { 18, 16, 22 };
const uint8_t WHEEL_DIR_PINS[] = { 17, 15, 21 };
const uint8_t WHEEL_PWM_CHANNELS[] = { 3, 4, 5 };