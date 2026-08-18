#include "DriveController.hpp"

DriveController::DriveController()
{

}

void DriveController::setUp()
{
    for(int i = 0; i < 3; i++)
    {
        pinMode(WHEEL_DIR_PINS[i], OUTPUT);
        pinMode(WHEEL_PWM_PINS[i], OUTPUT);
        ledcSetup(WHEEL_PWM_CHANNELS[i], 8000, 8);
        ledcAttachPin(WHEEL_PWM_PINS[i], WHEEL_PWM_CHANNELS[i]);
    }
}

void DriveController::setSpeed(int motorNum, int speed)
{
    if (motorNum >= 0 && motorNum < 3)
    {
        digitalWrite(WHEEL_DIR_PINS[motorNum], (speed > 0 ? HIGH : LOW));
        ledcWrite(WHEEL_PWM_CHANNELS[motorNum], constrain(abs(speed), 0, 255));
    }
}

void DriveController::drive(Structs::VectorFloat vec, float turn, float power)
{
    vec.x = 2*vec.x - 1;
    vec.y = 2*vec.y - 1;
    turn = 2*turn - 1;
    float speeds[3] = {0, 0, 0};
    speeds[0] = rGain * turn + vec.x;
    speeds[1] = rGain * turn + (vec.x/2 - vec.y*sqrt(3)/2);
    speeds[2] = rGain * turn + (vec.x/2 + vec.y*sqrt(3)/2);

    // speedが最大値を超えないように正規化しつつ、最大まで速度を出す
    float maxSpeed = max(max(abs(speeds[0]), abs(speeds[1])), abs(speeds[2]));
    for(int i = 0; i < 3; i++)
    {
        speeds[i] = (maxSpeed != 0 ? speeds[i] / maxSpeed * power * 255 : 0);
        setSpeed(i, (int)speeds[i]);
        //Serial.printf("Motor %d: %f\n", i, speeds[i]);
    }
}