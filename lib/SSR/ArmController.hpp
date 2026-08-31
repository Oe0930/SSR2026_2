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
        void setUp(int pin, int defaultAngle, int _minAngle, int _maxAngle);

        void set(int angle);
        void move(float speed);
};

class RotationServoController
{
    private:
        int minUs = 700;
        int maxUs = 2300;
        int baseUs = 1500;
        int usRange = 800;
        Servo servo;

    public:
        RotationServoController();
        void setUp(int pin, int _baseUs, int _usRange);

        void move(float speed);
};