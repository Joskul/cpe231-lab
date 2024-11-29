#pragma once

#include <vector>
#include <random>
#include <algorithm>
#include <bitset>

#define DEBUG
#define DEBUG_LEVEL DEBUG_LEVEL_INFO
#include "../utils/debug.hpp"

// Knapsack Algorithm : Dynamic Programming Approach
inline std::vector<int> knapsackDP(const std::vector<int> &costs, const std::vector<int> &values, int maxWt)
{
    std::vector<int> maxValueAtCapacity(maxWt + 1, 0);
    for (int item = 0; item < costs.size(); ++item)
    {
        for (int capacity = maxWt; capacity >= costs[item]; --capacity)
        {
            maxValueAtCapacity[capacity] = std::max(maxValueAtCapacity[capacity], maxValueAtCapacity[capacity - costs[item]] + values[item]);
        }
    }
    return maxValueAtCapacity;
}

// Knapsack Algorithm : Genetic Algorithm Approach
inline int fitness(uint32_t chromosome, const std::vector<std::pair<int, int>> &wtVal, int maxWt)
{
    int totalVal = 0, totalWt = 0;
    for (int i = 0; i < wtVal.size(); i++)
    {
        if (chromosome & (1 << i))
        {
            totalWt += wtVal[i].first;
            totalVal += wtVal[i].second;
        }
    }

    if (totalWt > maxWt)
    {
        return INT_MIN; // Illegal
    }
    else
    {
        return totalVal;
    }
}

inline uint32_t randInt(int l = 0, int r = 1)
{
    std::random_device rd;                       // obtain a random number from hardware
    std::mt19937 gen(rd());                      // seed the generator
    std::uniform_int_distribution<> distr(l, r); // define the range

    return distr(gen);
}

inline std::vector<std::pair<uint32_t, int>>::iterator pickRandom(std::vector<std::pair<uint32_t, int>> &pop)
{
    // Extract fitnesses
    std::vector<int> fitnesses(pop.size());
    for (const auto &chr : pop)
    {
        fitnesses.push_back(chr.second == INT_MIN ? 0 : chr.second);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d(fitnesses.begin(), fitnesses.end());

    return pop.begin() + (size_t)d(gen);
}

inline uint32_t crossover(uint32_t a, uint32_t b, uint32_t mask)
{
    uint32_t res = 0;
    for (int i = 0; i < 32; i++)
    {
        if ((mask & (1 << i)) == 0)
        {
            res |= (a & (1 << i));
        }
        else
        {
            res |= (b & (1 << i));
        }
    }
    return res;
}

inline uint32_t mutate(uint32_t chr, int chrLen, float mutRate = 0.05)
{
    if ((float)randInt(0, 100) / 100.0f < mutRate)
    {
        for (int i = 0; i < std::ceil(mutRate); i++) // Mutate more genes as mutRate increases
        {
            int mutIndex = randInt(0, chrLen); // Randomly pick a gene to mutate
            chr = chr ^ (1 << mutIndex);       // Flip the gene
        }
    }
    return chr;
}

inline int knapSackGA(const std::vector<std::pair<int, int>> &wtVal, int maxWt)
{
    const int chrLen = wtVal.size();
    const int popSize = chrLen * 10;
    std::vector<std::pair<uint32_t, int>> population(popSize, {0, 0}); // Chromosome and Fitness
    int popFitness = 0;
    float mutRate = 0.05f; // 5% mutation rate by default

    // Initialization : Generate the Population
    for (int i = 0; i < popSize; i++)
    {
        population[i].first = randInt(0, pow(2, chrLen));
        population[i].second = fitness(population[i].first, wtVal, maxWt);
        if (population[i].second == INT_MIN)
        {
            i--; // retry generating
            DB(std::cout << "Illegal Chromosome Generated! Trying again..." << std::endl;, DEBUG_LEVEL_INFO)
        }
        else
        {
            popFitness += population[i].second;
        }
    }

    popFitness /= popSize;

    int genCounter = 1;
    while (genCounter < 1000)
    {
        // Sort the population by fitness
        std::sort(population.begin(), population.end(), [](const auto &a, const auto &b)
                  { return a.second > b.second; });

        std::vector<std::pair<uint32_t, int>> popNext(popSize, {0, 0});
        int popNextFitness = 0;

        // Elitism kicks in
        const int eliteRate = 3;
        for (int i = 0; i < eliteRate; i++)
        {
            popNext[i] = population[i];
            popNextFitness += popNext[i].second == INT_MIN ? 0 : popNext[i].second;
        }

        // Crossover mask
        uint32_t mask = 1;
        for (int i = 1; i < wtVal.size(); i++)
        {
            mask <<= 1;
            if (randInt())
            {
                mask += !(mask & 1);
            }
            else
            {
                mask += (mask & 1);
            }
        }
        DB(std::cout << "Mask: " << std::bitset<32>(mask) << std::endl;)

        // Perform crossovers
        for (int i = eliteRate; i < popSize; i++) // Start after elites
        {
            // Pick weighted randoms
            auto a = pickRandom(population);
            auto b = pickRandom(population);
            DB(std::cout << "randomized " << a - population.begin() << " and " << b - population.begin() << std::endl;)

            popNext[i].first = mutate(crossover(a->first, b->first, mask), chrLen); // Also perform mutation
            popNext[i].second = fitness(popNext[i].first, wtVal, maxWt);

            if (popNext[i].second == INT_MIN) // Illegal chromosome
            {
                mutRate += 0.001f; // increase mutation rate
                DB(std::cout << "Crossver failed! Current Mutation Rate: " << mutRate << std::endl;, DEBUG_LEVEL_INFO)
            }
            popNextFitness += popNext[i].second == INT_MIN ? 0 : popNext[i].second;
            DB(std::cout << "Crossver Success!" << std::endl;)
        }
        popNextFitness /= popSize;

        // Move to the next generation
        population = popNext;
        popFitness = popNextFitness;
        genCounter++;

        DB(std::cout << "Generation " << genCounter << ": " << popFitness << std::endl;, DEBUG_LEVEL_INFO)
    }

    std::sort(population.begin(), population.end(), [](const auto &a, const auto &b)
              { return a.second > b.second; });
    DB(std::cout << std::bitset<32>(population[0].first) << std::endl;)

    return population[0].second;
}