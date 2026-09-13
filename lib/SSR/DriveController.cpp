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
    vec.y *= -1;
    turn = 2*turn - 1;

    vec.x *= power;
    vec.y *= power;
    turn *= power;

    if(isAccelarate)
    {
        long double timeGain = (long double)1 / accelTime;

        auto deltaVec = Structs::makeVectorFloat(vec.x - preVec.x, vec.y - preVec.y);

        long double deltaVecLength = sqrt(deltaVec.x*deltaVec.x + deltaVec.y*deltaVec.y);
        
        if(deltaVecLength != 0 && deltaVecLength > timeGain)
        {
            deltaVec.x *= timeGain / deltaVecLength;
            deltaVec.y *= timeGain / deltaVecLength;
        }

        vec = Structs::makeVectorFloat(preVec.x + deltaVec.x, preVec.y + deltaVec.y);
        turn = constrain(turn, preTurn - timeGain, preTurn + timeGain);
    }

    long double speeds[3] = {0, 0, 0};
    speeds[0] = -turn + vec.x;
    speeds[1] =  turn + (vec.x/2 - vec.y*sqrt(3)/2);
    speeds[2] =  turn + (vec.x/2 + vec.y*sqrt(3)/2);

    for(int i = 0; i < 3; i++) speeds[i] *= 255;

    // speedが最大値を超えないように正規化しつつ、最大まで速度を出す
    long double maxSpeed = max(max(abs(speeds[0]), abs(speeds[1])), abs(speeds[2]));

    for(int i = 0; i < 3; i++)
    {
        if(maxSpeed > 255) speeds[i] = (maxSpeed != 0 ? (speeds[i] / maxSpeed) * 255 : 0);

        speeds[i] = constrain(speeds[i], -255, 255);
        setSpeed(i, (int)speeds[i]);
    }

    preVec = vec;
    preTurn = turn;
}

void DriveController::stop()
{
    drive(Structs::makeVectorFloat(0,0), 0, 0, false);
}