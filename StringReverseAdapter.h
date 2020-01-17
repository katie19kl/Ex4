#ifndef StringReverseAdapter_h
#define StringReverseAdapter_h

#include "Solver.h"
#include <stdio.h>
#include "StringReverser.h"

template <typename Problem, typename Solution>

class StringReverseAdapter : public Solver <Problem,Solution> 
{
private:
    StringReverser reverser;
    /* data */
public:

    Solution solve(Problem &problem){
        //return reverser.reverseString(Problem::toString());
        return reverser.reverseString(problem.toString());
    }
};

#endif