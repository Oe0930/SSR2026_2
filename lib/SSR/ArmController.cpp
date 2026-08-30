#include "ArmController.hpp"

ServoController::ServoController()
{

}

void ServoController::setUp(int pin, int defaultAngle, int _minAngle, int _maxAngle)
{
    servo.setPeriodHertz(50);
    servo.attach(pin, minUs, maxUs);
    
    currentAngle = defaultAngle;
    servo.write(currentAngle);

    minAngle = _minAngle;
    maxAngle = _maxAngle;
}

void ServoController::set(int angle)
{
    currentAngle = constrain(angle, minAngle, maxAngle);
    servo.write(currentAngle);
}

void ServoController::move(float speed)
{
    if (speed == 0) return;

    currentAngle += speed;
    currentAngle = constrain(currentAngle, minAngle, maxAngle);
    servo.write((int)currentAngle);
}


RotationServoController::RotationServoController()
{

}

void RotationServoController::setUp(int pin, int _baseUs, int _usRange)
{
    baseUs = _baseUs;
    usRange = _usRange;
    minUs = baseUs - usRange;
    maxUs = baseUs + usRange;

    servo.setPeriodHertz(50);
    servo.attach(pin, minUs, maxUs);
}

void RotationServoController::move(float speed)
{
    servo.writeMicroseconds(constrain(baseUs + (int)(speed*usRange), minUs, maxUs));
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