#pragma once

#include <Arduino.h>
#include "InputManager.hpp"
#include "Structs.hpp"

extern InputManager input;
extern Structs::VectorFloat lStick;
extern Structs::VectorFloat rStick;
extern bool isA;
extern bool isB;
extern bool isX;
extern bool isY;
extern bool isL;
extern bool isR;
extern float zL;
extern float zR;
extern bool isRClicked;
extern bool isRClicked_pre;
extern bool isOpt;
extern bool isOpt_pre;

void updateInput();
void resetInput();
