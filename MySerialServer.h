#ifndef MySerialServer_h
#define MySerialServer_h

#include <asm/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Server.h"
#include "ClientHandler.h"

using namespace server_side;

class MySerialServer : public Server
{
public:

    void openParallel(int) override {}

    void open(int port, ClientHandler*c) {

        int socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd == -1)
        {
            std::cerr << "Could not create a socket" << std::endl;
            return;
        }
        // we first need to create the sockaddr obj.
        sockaddr_in address; //in means IP4
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
        address.sin_port = htons(port);

        //the actual bind command
        if (bind(socketfd, (struct sockaddr *)&address, sizeof(address)) == -1)
        {
            std::cerr << "Could not bind the socket to an IP" << std::endl;
            stop(-1, socketfd); //client_socket was not created - therefore sending -1
            return;
        }
        //making socket listen to the port
        if (listen(socketfd, 5) == -1)
        { //can also set to SOMAXCON (max connections)
            std::cerr << "Error during listening command" << std::endl;
            stop(-1, socketfd); //client_socket was not created - therefore sending -1
            return;
        }

        struct timeval tv;
        tv.tv_sec = 120; //2 minutes
        tv.tv_usec = 0;

        while (true) {
            // accepting a client

            if  (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv,
                           sizeof(tv)) < 0)  {}

            int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);//handling

            if (client_socket == -1) {
                cout << "error has occurred "<< errno << endl;
                stop(client_socket, socketfd);
                return;
            }

            c->handleClient(client_socket);

        }
    }
};

#endif