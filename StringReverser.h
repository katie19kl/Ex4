#ifndef _StringReverser_h_
#define _StringReverser_h_
#include "Solver.h"
#include <string>
#include <stdio.h>
#include <bits/stdc++.h>
#include "String.h"

using namespace std;



class StringReverser
{
private:
    String problem;
public:
    StringReverser(string toPut) : problem(toPut) {
        
    }
    string reverseString (string toReverse){ 
        reverse(toReverse.begin(), toReverse.end()); 
        return toReverse;
    }
    string toString (){
        return problem.toString();
    }
};

#endif