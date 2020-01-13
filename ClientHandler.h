#ifndef _ClientHandler_h_
#define _ClientHandler_h_

#include <stdio.h>
#include <string.h>
using namespace std;

class ClientHandler
{
private:
public:
    virtual string handleClient(int port) = 0;
};
#endif

