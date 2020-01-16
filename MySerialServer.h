#ifndef MySerialServer_h
#define MySerialServer_h

#include "Server.h"
#include "ClientHandler.h"
class MySerialServer : public Server
{
public:
    void open(int port, ClientHandler*c){
        c->handleClient(port);
    }
    void stop(){

    }   
};

#endif