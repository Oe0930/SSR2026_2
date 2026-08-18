#include <Arduino.h>
#include <PS4Controller.h>
#include "Structs.hpp"

class InputManager
{
    private:
        int roundValue(int value);
        float normalization(int value, int min, int max);

    public:
        InputManager();
        void connect();

        bool isConnected();

        Structs::VectorInt LStick();
        Structs::VectorFloat LStick(bool isFloat);
        Structs::VectorInt RStick();
        Structs::VectorFloat RStick(bool isFloat);

        bool A(); // O
        bool B(); // X
        bool X(); // □
        bool Y(); // △
        bool R();
        float ZR();
        bool L();
        float ZL();
        bool ps();
        bool option();
};