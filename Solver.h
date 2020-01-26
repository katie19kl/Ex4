#ifndef _Solver_h_
#define _Solver_h_
#include <stdio.h>
#include <string>
#include "ISearcher.h"

using namespace std;

template <typename  Problem , typename Solution, typename T>

class Solver
{
public:
    virtual Solution solve(Problem&) = 0;

    virtual Solution solve(Problem *) = 0;

    virtual void SetSearcher( ISearcher<T , Solution>*) = 0;
    
    virtual ~Solver(){}
};
#endif