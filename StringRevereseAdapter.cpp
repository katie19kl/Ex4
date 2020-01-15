#ifndef StringRevereseAdapter_h
#define StringRevereseAdapter_h

#include "Solver.h"
#include <stdio.h>
#include "StringReverser.h"

template <typename Problem, typename Solution>

class StringRevereseAdapter : public Solver <Problem,Solution> 
{
private:
    StringReverser reverser;
    /* data */
public:
    string solve(Problem problem){
        reverser.reverse(problem);
    }
};

#endif