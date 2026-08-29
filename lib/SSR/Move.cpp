#include "Move.hpp"

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
                drive.drive(std::get<0>(autoMove[i]), std::get<1>(autoMove[i]), std::get<2>(autoMove[i]));
                break;
            }
            _sumTime += std::get<3>(autoMove[i]);
        }
    }
}
