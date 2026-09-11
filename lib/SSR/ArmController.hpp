#include <Arduino.h>
#include <ESP32Servo.h>
#include "pins.hpp"

class ServoController
{
    private:
        int pin;
        int minUs = 500;
        int maxUs = 2400;
        float currentAngle = 0;
        Servo servo;

        int minAngle;
        int maxAngle;


        unsigned long lastUsedTime = 0;
        float lastAngle = -1;

    public:
        bool isAttached = false;
        ServoController();
        void setUp(int pin, int defaultAngle, int _minAngle, int _maxAngle);
        void attach();
        void detach();

        void set(float angle);
        void move(float speed);
};

class RotationServoController
{
    private:
        int pin = -1;
        int minUs = 700;
        int maxUs = 2300;
        int baseUs = 1500;
        int usRange = 800;
        int lastUs = -1;
        unsigned long lastUsedTime = 0;
        Servo servo;

    public:
        bool isAttached = false;
        RotationServoController();
        void setUp(int pin, int _baseUs, int _usRange);
        void attach();
        void detach();

        void move(float speed);
};