#pragma once

#include "PS4Controller.h"
#include "InputManager.hpp"
#include "Structs.hpp"

class GestureManager
{
    private:
        InputManager inputManager;
        Structs::VectorInt preTouchPosition;
        int dPos = 100;

        enum GestureDirection
        {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            UP_RIGHT,
            UP_LEFT,
            DOWN_RIGHT,
            DOWN_LEFT
        };
        
        struct Gesture
        {
            int id;
            std::vector<GestureDirection> directions;
        };

        std::vector<Gesture> gestures;
        std::vector<GestureDirection> currentDirections;

        GestureDirection getGestureDirection(const Structs::VectorInt& deltaPos);
        
    public:
        GestureManager();
        void Init(InputManager inputMgr);

        void update();

        int fingerCount();
        std::vector<GestureDirection> getGestureDirections();

        int lastGestureId = -1;
        int getGestureId();

        void ClearGestureDirections();
};



