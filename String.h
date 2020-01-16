#ifndef _String_h_
#define _String_h_

#include <string>
#include <stdio.h>

using namespace std;

class String
{
private:
    string problem;
public:
    String(string problemOutside){
        this->problem = problemOutside;
    }
    string toString (){
        return this->problem;
    }
};
#endif