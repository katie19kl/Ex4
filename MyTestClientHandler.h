#ifndef _MyTestClientHandler_h_
#define _MyTestClientHandler_h_

#include "ClientHandler.h"
#include <stdio.h>
#include <string>

using namespace std;

class MyTestClientHandler:public ClientHandler 
{
private:
    /* data */
public:
    virtual string handleClient(int port){

    } 
};

#endif
