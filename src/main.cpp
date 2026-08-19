#include <Arduino.h>
#include "DriveController.hpp"
#include "ArmController.hpp"
#include "InputManager.hpp"


// ========== input ==========
InputManager input;
Structs::VectorFloat lStick;
Structs::VectorFloat rStick;
bool isA;
bool isB;
bool isX;
bool isY;
bool isL;
bool isR;
float zL;
float zR;
bool isOpt;
bool isOpt_pre = false;

LimitSwitch lmSWs[2];
bool isLimitPushed[2];

// ========== Drive ==========
DriveController drive;
float slowGain = 0.6;

// ========== Arm ==========
ServoController etc[2];
ServoController back;
RotationServoController lift;

const float servoSpeed = 0.001f;
const float backServoSpeed = 0.01f;
const float liftSpeed = 0.01f;

// ========== main ==========
bool isAuto = false;
unsigned long autoRunStartTime = 0;


// 入力を受け取って変数に格納
void updateInput()
{
    lStick = input.LStick(true);
    rStick = input.RStick(true);
    isA = input.A();
    isB = input.B();
    isX = input.X();
    isY = input.Y();
    isL = input.L();
    isR = input.R();
    zL = min(input.ZL(), 1.0f);
    zR = min(input.ZR(), 1.0f);
    isOpt_pre = isOpt;
    isOpt = input.option();

    isLimitPushed[0] = lmSWs[0].isPushed();
    isLimitPushed[1] = lmSWs[1].isPushed();
}

float lastDebugTime = 0.0f;
void debug()
{
    // 100msごとにデバッグ出力
    if(millis() - lastDebugTime > 100)
    {
        lastDebugTime = millis();
        
        Serial.printf("LX=%2f LY=%2f\n", lStick.x, lStick.y);
        Serial.printf("RX=%2f RY=%2f\n", rStick.x, rStick.y);
        Serial.printf("L= %d R= %d ZL=%.2f ZR=%.2f\n", isL, isR, zL, zR);

        if (isA) Serial.print("A ");
        if (isB) Serial.print("B ");
        if (isX) Serial.print("X ");
        if (isY) Serial.print("Y ");
        if (isL) Serial.print("L1 ");
        if (isR) Serial.print("R1 ");
        if(isOpt) Serial.print("OPT ");
        if (isA || isB || isX || isY || isL || isR || isOpt) Serial.println();

        if(isLimitPushed[0]) Serial.print("LMSW0 ");
        if(isLimitPushed[1]) Serial.print("LMSW1 ");
        if(isLimitPushed[0] || isLimitPushed[1]) Serial.println("");

        Serial.println("isAuto: " + String(isAuto));
    }
}

// 自律走行停止処理
void finishAuto()
{
    isAuto = false;
    drive.drive(Structs::makeVectorFloat(0, 0), 0, 0);
}

// モーターの制御
void move()
{
    if(!isAuto)
    {
        // optionボタンで自律制御開始
        if(isOpt && !isOpt_pre)
        {
            isAuto = true;
            autoRunStartTime = millis();
            return;
        }

        // LスティックとRスティックで移動しつつ、ZLで減速
        drive.drive(lStick, rStick.x, (float)1 - zL*slowGain);

        if(isX ^ isY)
        {
            etc[0].move(servoSpeed * (isX ? 1 : -1));
            etc[1].move(servoSpeed * (isX ? -1 : 1));
        }

        if(isL ^ isR)
        {
            back.move(backServoSpeed * (isL ? 1 : -1));
        }

        if(isA ^ isB)
        {
            lift.move(liftSpeed * (isA ? 1 : -1));
        }
    }
    else
    {
        // optionで自律制御の強制停止
        if(isOpt && !isOpt_pre)
        {
            finishAuto();
            return;
        }

        // 自動制御

        // tuple< 移動ベクトル, 回転量, パワー , 時間 >
        std::tuple<Structs::VectorFloat, float, float, unsigned long> autoMove[10];
        autoMove[0] = std::make_tuple(Structs::makeVectorFloat(0, 1), 0, 1, 1000);
        autoMove[1] = std::make_tuple(Structs::makeVectorFloat(1, 0), 0, -1, 1000);
        autoMove[2] = std::make_tuple(Structs::makeVectorFloat(0, -1), 0, 0.5f, 1000);
        autoMove[3] = std::make_tuple(Structs::makeVectorFloat(-1, 0), 0, -0.5f, 1000);
        autoMove[4] = std::make_tuple(Structs::makeVectorFloat(0, 0), 0, 1, 0); // time <= 0 で終了

        unsigned long _sumTime = 0;
        for(int i = 0; i < 10; i++)
        {
            if(std::get<3>(autoMove[i]) <= 0)
            {
                finishAuto();
                return;
            }

            auto passedTime = millis() - autoRunStartTime;
            if(_sumTime <= passedTime && passedTime < _sumTime + std::get<3>(autoMove[i]))
            {
                //etc[0].move(servoSpeed * (std::get<2>(autoMove[i]))); // テスト用
                drive.drive(std::get<0>(autoMove[i]), std::get<1>(autoMove[i]), std::get<2>(autoMove[i]));
                break;
            }
            _sumTime += std::get<3>(autoMove[i]);
        }
    }
}

// セットアップ
void setup() 
{
    Serial.begin(115200);

    input.connect();

    drive.setUp();

    etc[0].setUp(ETC_SERVO_PIN1, 90);
    etc[1].setUp(ETC_SERVO_PIN2, 90);
    back.setUp(BACK_SERVO_PIN, 90);
    lift.setUp(LIFT_SERVO_PIN);
}

void loop()
{
    if (input.isConnected()) 
    {
        Serial.println("Contoroller is Connected!");

        while(input.isConnected())
        {
            updateInput();
            debug();
            move();
        }

        Serial.println("Contoroller is Disconnected...");
    }
}