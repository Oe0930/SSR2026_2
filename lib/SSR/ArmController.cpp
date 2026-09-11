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