#include <Arduino.h>
#include "Move.hpp"

// ========== input ==========
InputManager input;
Structs::VectorFloat lStick;
Structs::VectorFloat rStick;
bool isA;
bool isB;
bool isX;
bool isY;
bool isL;
bool isR;
float zL;
float zR;
bool isOpt;
bool isOpt_pre = false;

// ========== Drive ==========
DriveController drive;
float slowGain = 0.6f;

// ========== Arm ==========
ServoController etc[2];
ServoController back;
RotationServoController lift;

const float servoSpeed = 0.001f;
const float backServoSpeed = 0.01f;
const float liftSpeed = 0.01f;

// ========== main ==========
bool isAuto = false;
unsigned long autoRunStartTime = 0;

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
    }
}