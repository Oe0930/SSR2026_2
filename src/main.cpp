#include <Arduino.h>
#include "Move.hpp"
#include "InputController.hpp"
#include "DebugController.hpp"

// セットアップ
void setup() 
{
    Serial.begin(115200);

    input.connect();

    drive.setUp();

    etc[0].setUp(ETC_SERVO_PIN1, 90);
    etc[1].setUp(ETC_SERVO_PIN2, 90);
    back.setUp(BACK_SERVO_PIN, 90);
    lift.setUp(LIFT_SERVO_PIN);
}

void loop()
{
    if (input.isConnected()) 
    {
        Serial.println("Contoroller is Connected!");

        while(input.isConnected())
        {
            updateInput();
            debug();
            move();
        }

        Serial.println("Contoroller is Disconnected...");

        // 接続が切れたときはモーターを止める
        resetInput();
        drive.setSpeed(0,0);
        drive.setSpeed(1,0);
        drive.setSpeed(2,0);
        lift.move(0);
    }
}