//
// Created by katie on 13/01/2020.
//

#ifndef _MyTestClientHandler_h_
#define _MyTestClientHandler_h_

#include "ClientHandler.h"
#include <stdio.h>
#include <string>
#include "Solver.h"
#include "CacheManager.h"

using namespace std;

class MyTestClientHandler:public ClientHandler {
 private:
  CacheManager<string, string> * cache;
  Solver<string, string> * solver;


 public:
  MyTestClientHandler(CacheManager<string, string> * cache_manager, Solver<string, string> * problem_solver) {
    this->cache = cache_manager;
    this->solver = problem_solver;
  }

  void handleClient(int port) override;

};

#endif