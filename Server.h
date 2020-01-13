#include <stdio.h>
#include <iostream>
#include "ClientHandler.h"
using namespace std;

class Server
{
private:
    
public:    
    virtual void open(int port, ClientHandler* c) = 0;
};
