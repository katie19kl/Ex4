#ifndef StringRevereseAdapter_h
#define StringRevereseAdapter_h

#include "Solver.h"
#include <stdio.h>
#include "StringReverser.h"

template <typename Problem, typename Solution>

class StringRevereseAdapter : public Solver 
{
private:
    StringReverser reverser;
    /* data */
public:
};

#endif