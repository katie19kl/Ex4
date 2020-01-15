#ifndef _MyTestClientHandler_h_
#define _MyTestClientHandler_h_

#include "ClientHandler.h"
#include <stdio.h>
#include <string>
#include "Solver.h"
#include "CacheManager.h"

using namespace std;

class MyTestClientHandler:public ClientHandler 
{
private:
    CacheManager <string ,string > * cache;
    Solver <string ,string> * solver;    
public:

    virtual string handleClient(int port){

    } 
};

#endif
