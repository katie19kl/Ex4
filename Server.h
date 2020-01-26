#ifndef _Server_h_
#define _Server_h_

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "ClientHandler.h"
using namespace std;

namespace server_side {

class Server
{
 public:
  virtual void open(int, ClientHandler*) = 0;

  virtual void openParallel(int) = 0;

  void stop(int client_socket, int serverSocketFd) {

      if (client_socket != -1) {
          close(client_socket);
      }

      if (serverSocketFd != -1) {
          close(serverSocketFd);
      }
  }

  virtual ~Server(){}
};
}
#endif