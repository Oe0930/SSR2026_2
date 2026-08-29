#include <Arduino.h>
#include <ESP32Servo.h>
#include "pins.hpp"

class ServoController
{
    private:
        int minUs = 500;
        int maxUs = 2400;
        float currentAngle = 0;
        Servo servo;

        int minAngle;
        int maxAngle;

    public:
        ServoController();
        void setUp(int pin, int defaultAngle, int _minAngle = 0, int _maxAngle = 180);

        void set(int angle);
        void move(float speed);
};

class RotationServoController
{
    private:
        int minUs = 700;
        int maxUs = 2300;
        Servo servo;

    public:
        RotationServoController();
        void setUp(int pin);

        void move(float speed);
};

//昇降機構のclassを作る(モーターがサーボじゃなければ)
class DCMotorController
{
    private:
        int motorPin;

    public:
        DCMotorController();
        void setUp(int pin);

        void move(float speed);
};