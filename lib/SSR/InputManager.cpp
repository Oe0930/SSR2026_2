#include "InputManager.hpp"
using IM = InputManager;

IM::InputManager()
{
    
}

void IM::connect()
{
    PS4.begin("EC:E3:34:D2:AB:6A");
    Serial.println("Waiting for PS4...");
}

int IM::roundValue(int value)
{
    int limit = 30;
    return (abs(value) < limit ? 0 : value);
}

float IM::normalization(int value, int min, int max)
{
    return (float)(value - min) / (max - min);
}

bool IM::isConnected()
{
    return PS4.isConnected();
}

Structs::VectorInt IM::LStick()
{
    Structs::VectorInt ret;

    ret.x = roundValue(PS4.LStickX());
    ret.x += (PS4.Right() ? 128 : 0) + (PS4.Left() ? -128 : 0);
    ret.x = constrain(ret.x, -127, 127);

    ret.y = roundValue(PS4.LStickY());
    ret.y += (PS4.Up() ? 128 : 0) + (PS4.Down() ? -128 : 0);
    ret.y = constrain(ret.y, -127, 127);
    return ret;
}

Structs::VectorFloat IM::LStick(bool isFloat)
{
    auto _LStick = LStick();
    Structs::VectorFloat ret;
    ret.x = normalization(_LStick.x, -128, 128);
    ret.y = normalization(_LStick.y, -128, 128);

    return ret;
}

Structs::VectorInt IM::RStick()
{
    Structs::VectorInt ret;
    ret.x = roundValue(PS4.RStickX());
    ret.y = roundValue(PS4.RStickY());

    return ret;
}

Structs::VectorFloat IM::RStick(bool isFloat)
{
    auto _RStick = RStick();
    Structs::VectorFloat ret;
    ret.x = normalization(_RStick.x, -128, 128);
    ret.y = normalization(_RStick.y, -128, 128);

    return ret;
}

bool IM::A()
{
    return PS4.Circle();
}
bool IM::B()
{
    return PS4.Cross();
}
bool IM::X()
{
    return PS4.Triangle();
}
bool IM::Y()
{
    return PS4.Square();
}
bool IM::L()
{
    return PS4.L1();
}
bool IM::R()
{
    return PS4.R1();
}
float IM::ZL()
{
    return normalization(roundValue(PS4.L2Value()), 0, 128);
}
float IM::ZR()
{
    return normalization(roundValue(PS4.R2Value()), 0, 128);
}
bool IM::ps()
{
    return PS4.PSButton();
}
bool IM::option()
{
    return PS4.Options();
}
