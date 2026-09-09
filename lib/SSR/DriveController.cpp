#include "DriveController.hpp"

DriveController::DriveController()
{
    for (int i = 0; i < 3; i++)
    {
        lastSpeed[i] = 0;
        lastDirection[i] = true;
        isInitialized[i] = false;
    }
}

void DriveController::setUp(bool _isReverse[3])
{
    preTime = millis();

    for(int i = 0; i < 3; i++)
    {
        pinMode(WHEEL_DIR_PINS[i], OUTPUT);
        pinMode(WHEEL_PWM_PINS[i], OUTPUT);
        ledcSetup(WHEEL_PWM_CHANNELS[i], 8000, 8);
        ledcAttachPin(WHEEL_PWM_PINS[i], WHEEL_PWM_CHANNELS[i]);

        isReverse[i] = _isReverse[i];
    }
}

void DriveController::setSpeed(int motorNum, int speed)
{
    if (motorNum >= 0 && motorNum < 3)
    {
        bool isPositive = speed >= 0;
        int absSpeed = constrain(abs(speed), 0, 255);

        bool directionChanged = (isPositive != lastDirection[motorNum]);
        int speedDiff = abs(absSpeed - abs(lastSpeed[motorNum]));
        bool isAlmostSame = (speedDiff <= speedThreshold && !directionChanged);

        if (isAlmostSame)
        {
            return;
        }

        if (motorNum != 0) isPositive = !isPositive;

        digitalWrite(WHEEL_DIR_PINS[motorNum], (isPositive ? HIGH : LOW));
        ledcWrite(WHEEL_PWM_CHANNELS[motorNum], absSpeed);

        lastSpeed[motorNum] = speed;
        lastDirection[motorNum] = isPositive;
    }
}

void DriveController::drive(Structs::VectorFloat vec, float turn, float power, bool isAccelarate)
{
    vec.x = 2*vec.x - 1;
    vec.y = 2*vec.y - 1;
    turn = 2*turn - 1;

    // vecの長さを1に正規化
    if(vec.x != 0 || vec.y != 0)
    {
        float length = sqrt(vec.x*vec.x + vec.y*vec.y);
        vec.x /= length;
        vec.y /= length;
    }

    long double speeds[3] = {0, 0, 0};
    speeds[0] = -rGain * turn + vec.x;
    speeds[1] = rGain * turn + (vec.x/2 - vec.y*sqrt(3)/2);
    speeds[2] = rGain * turn + (vec.x/2 + vec.y*sqrt(3)/2);

    //Serial.printf("turn : %2f , speed[0] : %2f , speed[1] : %2f , speed[2] : %2f \n", turn, speeds[0], speeds[1], speeds[2]);

    // speedが最大値を超えないように正規化しつつ、最大まで速度を出す
    long double maxSpeed = max(max(abs(speeds[0]), abs(speeds[1])), abs(speeds[2]));
    unsigned long passedTime = millis() - preTime;
    long double delta = 255 * (long double)passedTime / 200;

    for(int i = 0; i < 3; i++)
    {
        speeds[i] = (maxSpeed != 0 ? (speeds[i] / maxSpeed) * (long double)power * 255 : 0);
        if(isAccelarate) speeds[i] = constrain(speeds[i], prePower[i] - delta, prePower[i] + delta);
        speeds[i] = constrain(speeds[i], -255, 255);
        setSpeed(i, (int)speeds[i]);

        prePower[i] = speeds[i];
    }

    preTime = millis();
}

void DriveController::stop()
{
    drive(Structs::makeVectorFloat(0,0), 0, 0, true);
}