#pragma once

#define index(x,y) ((x + y * Renderer::width) * 4)

//namespace s
//{
//
//     Used to generate "random" numbers based off of varying inputs
//     Max value = 4294967295
//    unsigned int hash(unsigned int state)
//    {
//        state ^= 2747636419u;
//        state *= 2654435769u;
//        state ^= state >> 16;
//        state *= 2654435769u;
//        state ^= state >> 16;
//        state *= 2654435769u;
//        return state;
//    }
//     Linear Interpolation
//    unsigned char lerp(unsigned char origValue, unsigned char newValue, float speed)
//    {
//        return origValue + (newValue - origValue) * speed;
//    }
//}

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