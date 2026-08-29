#pragma once

#include <Arduino.h>
#include <tuple>
#include "DriveController.hpp"
#include "ArmController.hpp"
#include "InputManager.hpp"

extern InputManager input;
extern DriveController drive;
extern ServoController etc[2];
extern ServoController back;
extern RotationServoController lift;

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
extern bool isOpt;
extern bool isOpt_pre;
extern float slowGain;
extern const float servoSpeed;
extern const float backServoSpeed;
extern const float liftSpeed;
extern bool isAuto;
extern unsigned long autoRunStartTime;

void updateInput();
void debug();
void finishAuto();
void move();