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
#include "String.h"

using namespace std;

class MyTestClientHandler:public ClientHandler {
 private:
  CacheManager<String, string> * cache;
  Solver<String, string> * solver;


 public:
  MyTestClientHandler(CacheManager<String, string> * cache_manager, Solver<String, string> * problem_solver) {
    this->cache = cache_manager;
    this->solver = problem_solver;
  }

  void handleClient(int port) override;

};

#endif