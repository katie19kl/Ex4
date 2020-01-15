#include "FileCacheManager.h"
#include "CacheManager.h"

#include <string>
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include <unordered_map>

using namespace std;

template <typename Problem, typename Solution>

size_t FileCacheManager<Problem, Solution>::makeHash(const Problem &problem)
{
    size_t hashedProblem = hash<Problem>{}(problem);
    return hashedProblem;
}

template <typename Problem, typename Solution>

void FileCacheManager<Problem, Solution>::addSolutionToBase(const Solution &solution,
                                                            const Problem &problem)
{
    this->fileSolution.insert({makeHash(problem), solution});
}

template <typename Problem, typename Solution>
bool FileCacheManager<Problem, Solution>::existSolution(const Problem &problem)
{
    try
    {
        this->fileSolution.at(makeHash(problem));
        return true;
    }
    catch (const std::out_of_range &oor)
    {
        return false;
    }
}

template <typename Problem, typename Solution>

Solution FileCacheManager<Problem, Solution>:: getSolution(Problem& problem){
    return this->fileSolution.at(makeHash(problem));
}