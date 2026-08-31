#include "Move.hpp"

// ========== Drive ==========
DriveController drive;
float slowGain = 0.6f;

// ========== Arm ==========
ServoController etc[2];
ServoController back;
RotationServoController lift;

const float servoSpeed = 0.1f;
const float backServoSpeed = 0.01f;
const float liftSpeed = 1;

// ========== main ==========
bool isAuto = false;
unsigned long autoRunStartTime = 0;

// 自律走行停止処理
void finishAuto()
{
    isAuto = false;
    drive.stop();
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
        float lStickAbs = (lStick.x-0.5f)*(lStick.x-0.5f) + (lStick.y-0.5f)*(lStick.y-0.5f);
        lStickAbs = constrain(sqrt(lStickAbs), 0, 1.0f);
        float power = constrain(((float)1 - zL*slowGain) * constrain((lStickAbs + abs(rStick.x-0.5)*2)/2, 0, 1), 0, 1);
        drive.drive(lStick, rStick.x, power);

        if(isX ^ isY)
        {
            etc[0].move(servoSpeed * (isX ? 1 : -1));
            etc[1].move(servoSpeed * (isX ? -1 : 1));
        }
        else
        {
            etc[0].move(0);
            etc[1].move(0);
        }

        if(isL ^ isR)
        {
            back.move(backServoSpeed * (isL ? 1 : -1));
        }
        else
        {
            back.move(0);
        }

        if(isA ^ isB)
        {
            lift.move(liftSpeed * (isA ? 1 : -1));
        }
        else
        {
            lift.move(0);
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
        autoMove[0] = std::make_tuple(Structs::makeVectorFloat(0.5f, 1), 0.5f, 0.5f, 500);
        autoMove[0] = std::make_tuple(Structs::makeVectorFloat(0.5f, 0.0f), 0.5f, 0.5f, 500);
        autoMove[1] = std::make_tuple(Structs::makeVectorFloat(0.5f, 0.5f), 0.5f, 0, 0); // time <= 0 で終了

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
                drive.drive(std::get<0>(autoMove[i]), std::get<1>(autoMove[i]), std::get<2>(autoMove[i]));
                break;
            }
            _sumTime += std::get<3>(autoMove[i]);
        }
    }
}
