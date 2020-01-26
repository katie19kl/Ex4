//
// Created by katie on 23/01/2020.
//

#ifndef EX4_PARTC_PARALLELSERVER_H_
#define EX4_PARTC_PARALLELSERVER_H_

#include "Server.h"
#include "SearcherAdapter.h"
#include "CacheManager.h"
#include "Matrix.h"
#include "FileCacheManager.h"
#include "ClientHandler.h"
#include "MyClientSearchClientHandler.h"
#include <asm/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <thread>
#include <errno.h>

using namespace std;
using namespace server_side;

class ParallelServer: public Server {

  ClientHandler* createClientHandler(CacheManager<Matrix<CellMatrix>, string>* cache,
      Solver<Matrix<CellMatrix>, vector<State<CellMatrix>* >, CellMatrix> *solver) {

      ClientHandler* client_handler = new MyClientSearchClientHandler(cache, solver);
      return client_handler;
  }

  void open(int, ClientHandler*) {
  }

  void openParallel(int port) {

      vector<thread*> clientThreads;

      Solver<Matrix<CellMatrix>, vector<State<CellMatrix>* >, CellMatrix> *solver =
          new SearcherAdapter <Matrix<CellMatrix>, vector<State<CellMatrix>*>, CellMatrix>();
      CacheManager<Matrix<CellMatrix>, string> * cache =
          new FileCacheManager<Matrix<CellMatrix>, string>();

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
          stop(-1, socketfd); //client_socket wasn't declared yet - therefore is -1
          return;
      }
      //making socket listen to the port
      if (listen(socketfd, 5) == -1)
      { //can also set to SOMAXCON (max connections)
          std::cerr << "Error during listening command" << std::endl;
          stop(-1, socketfd); //client_socket wasn't declared yet - therefore is -1
          return;
      }

      struct timeval tv;
      tv.tv_sec = 120; //2 minutes
      tv.tv_usec = 0;

      // accepting a client
      while (true) {

          if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv, //setting timeout
                         sizeof(tv)) < 0){}

          int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);

          if (client_socket == -1) {

              cout << "error has occurred "<< errno << endl;
              stop(client_socket, socketfd);
              break;
          }

          ClientHandler* client_handler = createClientHandler(cache, solver);

          clientThreads.emplace_back(new thread(&ClientHandler::handleClient, client_handler,client_socket));

      }

      //going over all threads to make sure they join in case an exception was thrown while they are running
      for (unsigned long i = 0; i < clientThreads.size(); i++) {
          clientThreads.at(i)->join();
      }
  }
};

#endif //EX4_PARTC_PARALLELSERVER_H_
