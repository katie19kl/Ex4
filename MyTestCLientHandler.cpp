//
// Created by katie on 13/01/2020.
//

#include "MyTestCLientHandler.h"
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>

void MyTestClientHandler::handleClient(int port) {
  vector<string> vectorStrings;

  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1)
  {
    throw "Could not create a socket";
  }

  // we first need to create the sockaddr obj.
  sockaddr_in address; //in means IP4
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
  address.sin_port = htons(port);

  //the actual bind command
  if (bind(socketfd, (struct sockaddr *)&address, sizeof(address)) == -1)
  {
    throw "Could not bind the socket to an IP";
  }

  //making socket listen to the port
  if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
    throw "Error during listening command";
  } else {
    std::cout << "Server is now listening ..." << std::endl;
  }


  struct timeval tv;
  tv.tv_sec = 120; //2 minutes
  tv.tv_usec = 0;

  // accepting a client
  while (true) {
    int client_socket = accept(socketfd, (struct sockaddr *)&address, (socklen_t *)&address);
    if (client_socket == -1) {
      throw  "Error accepting client";
    }

    try {
      setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
      char buffer[2048];
      read(client_socket, buffer, 2048);
      /*while (read(client_socket, buffer, 2048)) { //while data is transferred
        vectorStrings.emplace_back(buffer);
      }*/

      string problem(buffer);
      string solution;

      if (this->cache->existSolution(problem)) {
        solution = this->cache->getSolution(problem);
      } else {
        solution = this->solver->solve(problem);
        this->cache->addSolutionToBase(solution, problem);
      }

      char solutionArr[solution.length() + 1];
      strcpy(solutionArr, solution.c_str());
      send(client_socket, solutionArr, strlen(solutionArr), 0);

    } catch (exception& e) {
      if (client_socket != -1) {
        close(client_socket);
        exit(1);
      }
    }
  }
}