#include <Arduino.h>
#include "Move.hpp"
#include "InputController.hpp"
#include "DebugController.hpp"
#include "Gesture.hpp"

// セットアップ
void setup()
{
    Serial.begin(115200);

    input.connect();
    gesture.Init(input);

    pinMode(16, OUTPUT);

    digitalWrite(16, HIGH);
}

void moveTest()
{
    if(gesture.fingerCount() == 0)
    {
        int id = gesture.lastGestureId;

        if(id == 0)
        {
            digitalWrite(16, HIGH);
        }
        else if(id == 1)
        {
            digitalWrite(16, LOW);
        }
        
        gesture.lastGestureId = -1;
    }
}

void loop()
{
    static unsigned long lastRemovePairedDevices = 0;

    if (input.isConnected())
    {
        Serial.println("Contoroller is Connected!");

        while(input.isConnected())
        {
            updateInput();
            debug();
            gesture.update();

            moveTest();
        }

        Serial.println("Contoroller is Disconnected...");
    }
}