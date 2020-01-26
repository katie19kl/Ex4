//
// Created by katie on 13/01/2020.
//

#ifndef _MyTestClientHandler_h_
#define _MyTestClientHandler_h_

#include <stdio.h>
#include <string>
#include "String.h"
#include "Solver.h"
#include "CacheManager.h"
#include "ClientHandler.h"

using namespace std;

class MyTestClientHandler:public ClientHandler {
 private:
  CacheManager<String, string> * cache;
  Solver<String, string, string> * solver;


 public:
  MyTestClientHandler(CacheManager<String, string> * cache_manager, Solver<String, string, string> * problem_solver) {
    this->cache = cache_manager;
    this->solver = problem_solver;
  }

  void handleClient(int client_socket) override;

};

#endif