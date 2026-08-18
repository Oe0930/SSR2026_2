#include "ArmController.hpp"

ServoController::ServoController()
{

}

void ServoController::setUp(int pin, int defaultAngle)
{
    servo.setPeriodHertz(50);
    servo.attach(pin, minUs, maxUs);
    
    currentAngle = defaultAngle;
    servo.write(currentAngle);
}

void ServoController::set(int angle)
{
    currentAngle = constrain(angle, 0, 180);
    servo.write(currentAngle);
}

void ServoController::move(float speed)
{
    if (speed == 0) return;

    currentAngle += speed;
    currentAngle = constrain(currentAngle, 0.0f, 180.0f);
    servo.write((int)currentAngle);
}


RotationServoController::RotationServoController()
{

}

void RotationServoController::setUp(int pin)
{
    servo.setPeriodHertz(50);
    servo.attach(pin, minUs, maxUs);
}

void RotationServoController::move(float speed)
{
    if (speed == 0) return;
    int writeSpeed = constrain(90+speed*90, 0, 180);
    servo.write(writeSpeed);
}


DCMotorController::DCMotorController()
{
    motorPin = -1;
}

void DCMotorController::setUp(int pin)
{
    motorPin = pin;
    pinMode(motorPin, OUTPUT);
}

void DCMotorController::move(float speed)
{
    int pwmValue = (int)(constrain(abs(speed), 0.0f, 1.0f) * 255);
    analogWrite(motorPin, pwmValue);
}