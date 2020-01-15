#ifndef _FileCacheManager_h_
#define _FileCacheManager_h_
#include "CacheManager.h"

#include <stdio.h>
#include <iostream>
#include <unordered_map>
using namespace std;

template <typename Problem, typename Solution>

class FileCacheManager : public CacheManager<Problem, Solution>
{
private:
    std::unordered_map<size_t, Solution> fileSolution;

public:
    size_t makeHash(const Problem& problemem);
    bool existSolution(const Problem& problem);
    void addSolutionToBase(const Solution& solution,const Problem& problem);
};
#endif
