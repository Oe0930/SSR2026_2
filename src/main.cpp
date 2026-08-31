#include <Arduino.h>
#include "Move.hpp"
#include "InputController.hpp"
#include "DebugController.hpp"

// セットアップ
void setup() 
{
    Serial.begin(115200);

    input.connect();

    bool init[] = {false, false, false};
    drive.setUp(init);

    etc[0].setUp(ETC_SERVO_PIN1, 90, 0, 180);
    etc[1].setUp(ETC_SERVO_PIN2, 90, 0, 180);
    back.setUp(BACK_SERVO_PIN, 90, 0, 180);
    lift.setUp(LIFT_SERVO_PIN, 1500, 800);
}

void loop()
{
    if (input.isConnected()) 
    {
        Serial.println("Contoroller is Connected!");

        while(input.isConnected())
        {
            updateInput();
            //debug();
            move();
        }

        Serial.println("Contoroller is Disconnected...");

        // 接続が切れたときはモーターを止める
        resetInput();
        drive.stop();
        lift.move(0);
    }
}