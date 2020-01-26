#ifndef StringReverseAdapter_h
#define StringReverseAdapter_h

#include "Solver.h"
#include <stdio.h>
#include "StringReverser.h"

template <typename Problem, typename Solution, typename T>

class StringReverseAdapter : public Solver <Problem, Solution, T>
{
private:
    StringReverser reverser;
    /* data */
public:

    Solution solve(Problem &problem){
        return reverser.reverseString(problem.toString());
    }

    Solution solve(Problem *problem) {
        return reverser.reverseString(problem->toString());
    }

    void SetSearcher( ISearcher<T , Solution>*) {

    }

};

#endif