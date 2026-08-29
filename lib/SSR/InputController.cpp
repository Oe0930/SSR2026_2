#include "InputController.hpp"

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

void updateInput()
{
    lStick = input.LStick(true);
    rStick = input.RStick(true);
    isA = input.A();
    isB = input.B();
    isX = input.X();
    isY = input.Y();
    isL = input.L();
    isR = input.R();
    zL = min(input.ZL(), 1.0f);
    zR = min(input.ZR(), 1.0f);
    isOpt_pre = isOpt;
    isOpt = input.option();
}

void resetInput()
{
    lStick.x = 0;
    lStick.y = 0;

    rStick.x = 0;
    rStick.y = 0;

    isA = false;
    isB = false;
    isX = false;
    isY = false;
    isL = false;
    isR = false;
    zL = 0;
    zR = 0;
    isOpt = false;
    isOpt_pre = false;
}