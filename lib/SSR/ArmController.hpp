#include <Arduino.h>
#include <ESP32Servo.h>
#include "pins.hpp"

class ServoController
{
    private:
        int pin;
        int minUs = 500;
        int maxUs = 2400;
        int servoAngle = 0;
        float currentAngle = 0;
        Servo servo;


        unsigned long lastUsedTime = 0;
        float lastAngle = -1;
        bool autoDetach = true;

    public:

        int minAngle;
        int maxAngle;
        bool isAttached = false;
        ServoController();
        void setUp(int pin, int defaultAngle, int _minAngle, int _maxAngle);
        void attach();
        void detach();
        void setAutoDetach(bool enabled);

        void set(float angle);
        void move(float speed);
        void stop();
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
        void stop();
};
