#pragma once

class Utilities
{
public:
    static unsigned int hash(unsigned int state)
    {
        state ^= 2747636419u;
        state *= 2654435769u;
        state ^= state >> 16;
        state *= 2654435769u;
        state ^= state >> 16;
        state *= 2654435769u;
        return state;
    }
    static constexpr float PI = 3.1415926535f;
};