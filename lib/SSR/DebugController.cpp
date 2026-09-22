#include "DebugController.hpp"
#include "InputController.hpp"
#include "Move.hpp"

float lastDebugTime = 0.0f;

void debug()
{
    if(millis() - lastDebugTime > 100)
    {
        lastDebugTime = millis();

        
        /*
        Serial.printf("LX=%2f LY=%2f\n", lStick.x, lStick.y);
        Serial.printf("RX=%2f RY=%2f\n", rStick.x, rStick.y);
        Serial.printf("L= %d R= %d ZL=%.2f ZR=%.2f\n", isL, isR, zL, zR);

        
        if (isA) Serial.print("A ");
        if (isB) Serial.print("B ");
        if (isX) Serial.print("X ");
        if (isY) Serial.print("Y ");
        if (isL) Serial.print("L1 ");
        if (isR) Serial.print("R1 ");
        if(isOpt) Serial.print("OPT ");
        if (PS4.Touchpad()) Serial.print("TOUCH ");
        if (isA || isB || isX || isY || isL || isR || isOpt || PS4.Touchpad()) Serial.println();
        */
        

        //Serial.println("isAuto: " + String(isAuto));
        
        //Serial.printf("Gyro: %d %d %d\n", PS4.GyrX(), PS4.GyrY(), PS4.GyrZ());
        //Serial.printf("Accel: %d %d %d\n", PS4.AccX(), PS4.AccY(), PS4.AccZ());

        for (uint8_t i = 0; i < 2; ++i) 
        {
            if (PS4.TouchpadTouchActive(i)) 
            {
                Serial.printf(
                    "touch=%u id=%u x=%u y=%u timestamp=%u\n",
                    i,
                    PS4.TouchpadTouchID(i),
                    PS4.TouchpadX(i),
                    PS4.TouchpadY(i),
                    PS4.TouchpadTimestamp()
                );
            }
        }

        auto gestureDirections = gesture.getGestureDirections();
        Serial.printf("Gesture Direction: ");
        for (const auto& dir : gestureDirections) {
            Serial.printf(dir == 0 ? "UP " :
                          dir == 1 ? "DOWN " :
                          dir == 2 ? "LEFT " :
                          dir == 3 ? "RIGHT " :
                          dir == 4 ? "UP_RIGHT " :
                          dir == 5 ? "UP_LEFT " :
                          dir == 6 ? "DOWN_RIGHT " :
                          dir == 7 ? "DOWN_LEFT " : "UNKNOWN ");
        }
        Serial.println();

        if(gesture.getGestureId() != -1)
        {
            Serial.printf("Gesture ID: %d\n", gesture.getGestureId());
        }

        //Serial.printf("Sensor Temperature: %u\n", PS4.SensorTemperature());
        
        //Serial.printf("Battery Level : %d\n", PS4.Battery());



        //Serial.print("Lift.isAttached : ");
        //Serial.println(lift.isAttached ? "True" : "False");
    }
}
