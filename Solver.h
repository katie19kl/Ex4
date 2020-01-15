#ifndef _Solver_h_
#define _Solver_h_
#include <stdio.h>
#include <string>

using namespace std;

template <typename Problem, typename Solution>

class Solver
{
private:
    /* data */
public:
    virtual string solve() = 0;
};
#endif