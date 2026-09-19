#include "Move.hpp"

// ========== Drive ==========
DriveController drive;
float slowGainL = 0.9f;
float slowGainR = 0.6f;

// ========== Arm ==========
ServoController etc[2];
ServoController back;
RotationServoController lift;

namespace
{
    void stopArmActuators()
    {
        etc[0].stop();
        etc[1].stop();
        back.stop();
        lift.stop();
    }
}

const float servoSpeed = 0.05f;
const float backServoSpeed = 0.05f;
const float liftSpeed = 1;

// ========== main ==========
int isAuto = 0; // 0: no, 1: 自律ゾーン+帰還, 2: 後ろアーム
unsigned long autoRunStartTime = 0;

// 自律走行停止処理
void finishAuto()
{
    isAuto = 0;
    drive.stop();
    stopArmActuators();
}

// モーターの制御
void move()
{
    if(isAuto == 0)
    {
        // optionボタンで自律制御開始
        if(isOpt && !isOpt_pre)
        {
            drive.stop();
            stopArmActuators();
            isAuto = 1;
            autoRunStartTime = millis();
            return;
        }

        if(isRClicked && !isRClicked_pre)
        {
            drive.stop();
            stopArmActuators();
            isAuto = 2;
            autoRunStartTime = millis();
            return;
        }

        // LスティックとRスティックで移動しつつ、ZLで減速
        float power = constrain(((float)1 - zL*slowGainL) * ((float)1 - zR*slowGainR), 0, 1);
        drive.drive(lStick, rStick.x, power, true);

        if(isX ^ isY)
        {
            etc[0].move(servoSpeed * (isX ? 1 : -1) * power);
            etc[1].move(servoSpeed * (isX ? -1 : 1) * power);
        }
        else
        {
            etc[0].move(0);
            etc[1].move(0);
        }

        if(isL ^ isR)
        {
            back.move(backServoSpeed * (isR ? 1 : -1) * power);
        }
        else
        {
            back.move(0);
        }

        if(isLClicked)
        {  
            back.detach();
        }

        if(isA ^ isB)
        {
            lift.move(liftSpeed * (isA ? -1 : 1));
        }
        else
        {
            lift.move(0);
        }
    }
    else if(isAuto == 1)
    {
        // optionで自律制御の強制停止
        if(isOpt && !isOpt_pre)
        {
            finishAuto();
            return;
        }

        // 自動制御
        // tuple< 移動ベクトル, 回転量, パワー , 時間 >
        static const std::tuple<Structs::VectorFloat, float, float, unsigned long, unsigned long> autoMove[] = {
            std::make_tuple(Structs::makeVectorFloat(0.5f, 1.0f), 0.5f, 1.0f, 2500UL, 2000UL),
            std::make_tuple(Structs::makeVectorFloat(1.0f, 0.5f), 0.5f, 1.0f, 1750UL, 1000UL),
            std::make_tuple(Structs::makeVectorFloat(0.46f, 0.0f), 0.5f, 0.6f, 5400UL, 1000UL),
            std::make_tuple(Structs::makeVectorFloat(1.0f, 0.5f), 0.5f, 1.0f, 2000UL, 1000UL),
            std::make_tuple(Structs::makeVectorFloat(0.5f, 0.5f), 0.5f, 0.0f, 500UL, 1000UL),
            std::make_tuple(Structs::makeVectorFloat(0.0f, 0.5f), 0.5f, 1.0f, 2000UL, 1000UL),
            std::make_tuple(Structs::makeVectorFloat(0.5f, 1.0f), 0.5f, 1.0f, 3400UL, 1000UL),
            std::make_tuple(Structs::makeVectorFloat(0.0f, 0.5f), 0.5f, 1.0f, 1750UL, 1000UL),
            std::make_tuple(Structs::makeVectorFloat(0.5f, 0.0f), 0.5f, 1.0f, 1750UL, 1000UL),
            std::make_tuple(Structs::makeVectorFloat(0.5f, 0.5f), 0.5f, 0.0f, 0UL, 1000UL) // time <= 0 で終了
        };

        unsigned long _sumTime = 0;
        for(size_t i = 0; i < sizeof(autoMove) / sizeof(autoMove[0]); i++)
        {
            if(std::get<3>(autoMove[i]) <= 0)
            {
                finishAuto();
                return;
            }

            auto passedTime = millis() - autoRunStartTime;
            if(_sumTime <= passedTime && passedTime < _sumTime + std::get<3>(autoMove[i]))
            {
                float power = std::get<2>(autoMove[i]);
                auto accelTime = std::get<4>(autoMove[i]);
                if (passedTime - _sumTime < accelTime) power *= (float)(passedTime - _sumTime) / (float)accelTime;
                if (_sumTime + std::get<3>(autoMove[i]) - passedTime < accelTime) power *= (float)(_sumTime + std::get<3>(autoMove[i]) - passedTime)/(float)accelTime;
                
                drive.drive(std::get<0>(autoMove[i]), constrain((std::get<1>(autoMove[i]) + rStick.x)/2, 0, 1), power, false);
                
                break;
            }
            _sumTime += std::get<3>(autoMove[i]);
        }
    }
    else if(isAuto == 2)
    {
        unsigned long passedTime = millis() - autoRunStartTime;
        unsigned long allTime = 2000;

        if((isRClicked && !isRClicked_pre) || passedTime > allTime)
        {
            finishAuto();
            return;
        }

        // 自動制御
        back.set(back.minAngle + (back.maxAngle - back.minAngle)*(float)passedTime / (float)allTime);

        float maxPower = 0.1f;
        drive.drive(Structs::makeVectorFloat(0.5f, 0.0f), 0.5f, maxPower * std::sin((3.14159f/2.0f) * (float)passedTime / (float)allTime), false);
    }
}
