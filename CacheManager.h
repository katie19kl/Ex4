#ifndef _CacheManager_h_
#define _CacheManager_h_
#include <stdio.h>

template <typename Problem, typename Solution>

class CacheManager
{
public:
    virtual bool existSolution(Problem&) = 0;

    virtual void addSolutionToBase(Solution&,Problem&) = 0;

    virtual Solution getSolution(Problem&) = 0;

    virtual ~CacheManager(){}
};
#endif
