#ifndef _ClientHandler_h_
#define _ClientHandler_h_

#include <stdio.h>
#include <string>
using namespace std;

class ClientHandler
{
private:
public:
    virtual string handleClient(int socket) = 0;
};
#endif

