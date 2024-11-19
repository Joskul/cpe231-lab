#pragma once
#include "../utils/debug.hpp"

#include <vector>
#include "../utils/arrayUtils.hpp"

inline std::vector<int> primeInRange(int n)
{
    std::vector<int> res = range(2, n + 1);
    DB(int opCount = 0;) // erase count

    for (std::vector<int>::iterator num = res.begin(); num < res.end(); num++)
    {
        auto p = num + *num;
        for (; p <= res.end(); p += *num)
        {
            DB(std::cout << "Erased " << *p << std::endl;)
            res.erase(p);
            DB(opCount++;)
            p--;
        }
    }

    DB(std::cout << "Total Erase : " << opCount << std::endl;)

    return res;
}