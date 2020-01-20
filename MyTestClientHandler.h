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
    CacheManager* cache;
    Solver* solver;    
public:

    virtual string handleClient(int socket){

    } 
};

#endif