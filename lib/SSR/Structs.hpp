#pragma once

#include <vector>

namespace Structs
{
    struct VectorInt
    {
        int x = 0;
        int y = 0;

        inline VectorInt operator+(const VectorInt& other) const
        {
            VectorInt ret;
            ret.x = x + other.x;
            ret.y = y + other.y;
            return ret;
        }

        inline VectorInt operator-(const VectorInt& other) const
        {
            VectorInt ret;
            ret.x = x - other.x;
            ret.y = y - other.y;
            return ret;
        }

        inline VectorInt& operator+=(const VectorInt& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        inline VectorInt& operator-=(const VectorInt& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }
    };

    struct VectorFloat
    {
        float x = 0;
        float y = 0;
    };

    inline VectorInt makeVectorInt(int x, int y)
    {
        VectorInt ret;
        ret.x = x;
        ret.y = y;
        return ret;
    }



    inline VectorFloat makeVectorFloat(float x, float y)
    {
        VectorFloat ret;
        ret.x = x;
        ret.y = y;
        return ret;
    }
};