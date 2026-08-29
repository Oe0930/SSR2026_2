#pragma once

#include <Arduino.h>
#include <tuple>
#include "DriveController.hpp"
#include "ArmController.hpp"
#include "InputController.hpp"

extern DriveController drive;
extern ServoController etc[2];
extern ServoController back;
extern RotationServoController lift;
extern float slowGain;
extern const float servoSpeed;
extern const float backServoSpeed;
extern const float liftSpeed;
extern bool isAuto;
extern unsigned long autoRunStartTime;

void finishAuto();
void move();