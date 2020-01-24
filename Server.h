#ifndef _Server_h_
#define _Server_h_

#include <stdio.h>
#include <iostream>
#include "ClientHandler.h"
using namespace std;

class Server
{
private:
    
public:    
    virtual void open(int, ClientHandler*) = 0;

    virtual void openParallel(int) = 0;

    virtual ~Server(){}
};
#endif