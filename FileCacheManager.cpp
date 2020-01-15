#include "FileCacheManager.h"
#include "CacheManager.h"

#include <string>
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include <unordered_map>

using namespace std;

template <typename Problem, typename Solution>

void FileCacheManager<Problem, Solution>::addSolutionToBase(const Solution &solution,
                                                            const Problem &problem)
{
    this->fileSolution.insert({Problem::toString(), solution});
}

template <typename Problem, typename Solution>
bool FileCacheManager<Problem, Solution>::existSolution(const Problem &problem)
{

    if (this->fileSolution.find(Problem::toString() == this->fileSolution.end())){
        return false;
    }
    return true;
}

template <typename Problem, typename Solution>

Solution FileCacheManager<Problem, Solution>::getSolution(Problem &problem)
{
    return this->fileSolution.at(Problem::toString());
}