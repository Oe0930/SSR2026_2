#### 操作方法

##### 移動
- Lスティック
- 十字キー

##### 回転
- Rスティック

##### アーム操作
- X,Y (ETC)
- A,B (ラック)
- L,R (バック)

##### 減速 (移動とアーム両方？)
- ZL
- ZR

##### 自律制御
- OPTION

## PIN
- ETC_SERVO_PIN1 = 32;
- ETC_SERVO_PIN2 = 34;
- LIFT_SERVO_PIN = 27;
- BACK_SERVO_PIN = 13;

0 : 後輪、1 : 右前輪、2 : 左前輪
- WHEEL_PWM_PINS[] = { 18, 16, 22 };
- WHEEL_DIR_PINS[] = { 17, 15, 21 };
- WHEEL_PWM_CHANNELS[] = { 3, 4, 5 };