#include "DebugController.hpp"
#include "InputController.hpp"
#include "Move.hpp"

float lastDebugTime = 0.0f;

void debug()
{
    if(millis() - lastDebugTime > 100)
    {
        lastDebugTime = millis();

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
        if (isA || isB || isX || isY || isL || isR || isOpt) Serial.println();

        Serial.println("isAuto: " + String(isAuto));
        
        Serial.printf("Battery Level : %d\n", PS4.Battery());

        Serial.print("Lift.isAttached : ");
        Serial.println(lift.isAttached ? "True" : "False");
    }
}
