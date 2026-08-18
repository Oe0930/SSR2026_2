#include <Arduino.h>
#include "pins.hpp"
#include "Structs.hpp"

class DriveController
{
    private:
        int defaultSpeed;
        int slowSpeed;
        
        int rGain = 1;

    public:
        DriveController();
        void setUp();

        void setSpeed(int motorNum, int speed);
        void drive(Structs::VectorFloat vec, float turn,float power);
};