#pragma once
#include "../utils/debug.hpp"

inline int findGcd(int a, int b)
{
    DB(int opCount = 0;)
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
        DB(opCount++;)
    }
    DB(std::cout << "Total Operations (Modulo) : " << opCount << std::endl;)
    return a;
}