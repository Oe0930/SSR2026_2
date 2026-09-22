#include "Gesture.hpp"

GestureManager gesture;

GestureManager::GestureManager()
{

}

void GestureManager::Init(InputManager inputMgr)
{
    inputManager = inputMgr;
    ClearGestureDirections();

    Gesture gesture;
    gesture.id = 0;
    gesture.directions = {GestureManager::GestureDirection::LEFT, GestureManager::GestureDirection::RIGHT};
    gestures.push_back(gesture);
    
    gesture.id = 1;
    gesture.directions = {GestureManager::GestureDirection::RIGHT, GestureManager::GestureDirection::LEFT};
    gestures.push_back(gesture);
}

void GestureManager::update()
{
    if (fingerCount() == 0)
    {
        lastGestureId = getGestureId();
        ClearGestureDirections();
        return;
    }

    auto touchPosition = inputManager.TouchpadPosition(0);
    auto deltaPos = touchPosition - preTouchPosition;

    if (preTouchPosition.x == -1 && preTouchPosition.y == -1)
    {
        preTouchPosition = touchPosition;
        return;
    }
    
    if (deltaPos.x*deltaPos.x + deltaPos.y*deltaPos.y < dPos*dPos)
    {
        return;
    }

    GestureDirection direction = getGestureDirection(deltaPos);

    if(currentDirections.empty() || currentDirections.at(currentDirections.size() - 1) != direction)
    {
        currentDirections.push_back(direction);
    }
    
    preTouchPosition = touchPosition;
}

int GestureManager::fingerCount()
{
    return inputManager.fingerCount();
}

std::vector<GestureManager::GestureDirection> GestureManager::getGestureDirections()
{
    return currentDirections;
}

int GestureManager::getGestureId()
{
    int ret = -1;

    for (const auto& gesture : gestures)
    {
        if(gesture.directions == currentDirections)
        {
            ret = gesture.id;
            break;
        }
    }

    return ret;
}

void GestureManager::ClearGestureDirections()
{
    currentDirections.clear();
    preTouchPosition = Structs::makeVectorInt(-1, -1);
}

GestureManager::GestureDirection GestureManager::getGestureDirection(const Structs::VectorInt& deltaPos)
{
    if (abs(deltaPos.x) > abs(deltaPos.y))
    {
        if (deltaPos.x > 0)
            return RIGHT;
        else
            return LEFT;
    }
    else
    {
        if (deltaPos.y > 0)
            return DOWN;
        else
            return UP;
    }
}