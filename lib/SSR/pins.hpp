#pragma once

const uint8_t ETC_SERVO_PIN1 = 2;
const uint8_t ETC_SERVO_PIN2 = 4;
const uint8_t BACK_SERVO_PIN = 5;
const uint8_t LIFT_SERVO_PIN = 33;

// 0 : 後輪 
// 1 : 右前輪 
// 2 : 左前輪 
const uint8_t WHEEL_DIR_PINS[] = { 13, 14, 25 };
const uint8_t WHEEL_PWM_PINS[] = { 12, 27, 26 };
const uint8_t WHEEL_PWM_CHANNELS[] = { 3, 4, 5 };