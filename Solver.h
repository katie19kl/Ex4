#ifndef _Solver_h_
#define _Solver_h_
#include <stdio.h>
#include <string>

using namespace std;

//template <class T, template <class> class Problem> 
template <typename  Problem , typename Solution>

class Solver
{
private:
    /* data */ 
public:
    virtual Solution solve(Problem&) = 0;
};
#endif