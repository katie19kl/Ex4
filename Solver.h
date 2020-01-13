#ifndef _Solver_h_
#define _Solver_h_
#include <stdio.h>
#include <string>

using namespace std;

class Solver
{
private:
    /* data */
public:
    virtual string solve() = 0;
};
#endif