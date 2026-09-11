#include "ArmController.hpp"

ServoController::ServoController()
{

}

void ServoController::setUp(int _pin, int defaultAngle, int _minAngle, int _maxAngle)
{
    servo.setPeriodHertz(50);
    pin = _pin;
    attach();
    
    set(currentAngle);

    lastAngle = defaultAngle;
    lastUsedTime = millis() - 5000;

    minAngle = _minAngle;
    maxAngle = _maxAngle;

    detach();
}

void ServoController::attach()
{
    if(!isAttached)
    {
        isAttached = true;
        servo.attach(pin);
    }
}

void ServoController::detach()
{
    if(isAttached)
    {
        isAttached = false;
        servo.detach();
    }
}

void ServoController::set(float angle)
{
    currentAngle = constrain(angle, minAngle, maxAngle);

    if(currentAngle == lastAngle)
    {
        if(millis() - lastUsedTime > 3000)
        {
            detach();
        }
    }
    else
    {
        lastAngle = currentAngle;
        lastUsedTime = millis();
        
        attach();
        servo.write((int)currentAngle);  
    }
}

void ServoController::move(float speed)
{
    set(currentAngle + speed);
}


RotationServoController::RotationServoController()
{

}

void RotationServoController::attach()
{
    if(!isAttached)
    {
        isAttached = true;
        servo.attach(pin, minUs, maxUs);
    }
}

void RotationServoController::detach()
{
    if(isAttached)
    {
        isAttached = false;
        servo.detach();
    }
}

void RotationServoController::setUp(int _pin, int _baseUs, int _usRange)
{
    pin = _pin;
    baseUs = _baseUs;
    usRange = _usRange;
    minUs = baseUs - usRange;
    maxUs = baseUs + usRange;

    servo.setPeriodHertz(50);
    attach();
    servo.writeMicroseconds(baseUs);
    lastUs = baseUs;
    lastUsedTime = millis() - 5000;
    detach();
}

void RotationServoController::move(float speed)
{
    int targetUs = constrain(baseUs + (int)(speed*usRange), minUs, maxUs);

    if(targetUs == lastUs)
    {
        if(millis() - lastUsedTime > 3000)
        {
            detach();
        }
    }
    else
    {
        lastUs = targetUs;
        lastUsedTime = millis();

        attach();
        servo.writeMicroseconds(targetUs);
    }
}