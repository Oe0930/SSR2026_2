#pragma once

namespace Structs
{
    struct VectorInt
    {
        int x = 0;
        int y = 0;
    };

    struct VectorFloat
    {
        float x = 0;
        float y = 0;
    };

    inline VectorFloat makeVectorFloat(float x, float y)
    {
        VectorFloat ret;
        ret.x = x;
        ret.y = y;
        return ret;
    }
};