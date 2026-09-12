#include <Arduino.h>
#include "pins.hpp"
#include "Structs.hpp"

class DriveController
{
    private:
        int defaultSpeed;
        int slowSpeed;
        const int speedThreshold = 2;

        Structs::VectorFloat preVec;
        float preTurn = 0;
        float prePower = 0;
        unsigned long preTime = 0;
        
        int rGain = 1;
        bool isReverse[3];
        int lastSpeed[3];
        bool lastDirection[3];
        bool isInitialized[3];

        unsigned long accelTime = 20000;

    public:
        DriveController();
        void setUp(bool _isReverse[3]);

        void setSpeed(int motorNum, int speed);
        void drive(Structs::VectorFloat vec, float turn, float power, bool isAccelarate);
        void stop();
};