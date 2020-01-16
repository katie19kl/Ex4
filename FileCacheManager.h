#ifndef _FileCacheManager_h_
#define _FileCacheManager_h_
#include "CacheManager.h"

#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

template <typename Problem, typename Solution>

class FileCacheManager : public CacheManager<Problem, Solution>
{
private:
    unordered_map<string, string> fileSolution;

public:
    bool existSolution(const Problem&);
    void addSolutionToBase(const Solution& solution, const Problem& problem);
    Solution getSolution(Problem&);
};
#endif
