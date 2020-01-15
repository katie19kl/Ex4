#ifndef _CacheManager_h_
#define _CacheManager_h_
#include <stdio.h>

template <typename Problem, typename Solution>

class CacheManager
{
public:
    virtual bool existSolution(const Problem& problem) = 0;

    virtual size_t makeHash(const Problem& problem) = 0;

    virtual void addSolutionToBase(const Solution& solution,const Problem& problem) = 0;
};
#endif
