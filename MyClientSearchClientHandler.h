/*#ifndef _MyClientSearchClientHandler_h
#define _MyClientSearchClientHandler_h_
#include "ClientHandler.h"
#include <string>
#include "Solver.h"
#include "CacheManager.h"
#include "Matrix.h"
#include "State.h"
#include <vector>

using namespace std;

class MyClientSearchClientHandler : public ClientHandler
{
private:
  CacheManager<Matrix, vector<State>> *cache;
  Solver<Matrix, vector<State>> *solver;

public:
  MyClientSearchClientHandler(CacheManager<Matrix, vector<State>> *cache_manager, Solver<Matrix, vector<State>> *problem_solver)
  {

    this->cache = cache_manager;
    this->solver = problem_solver;
  }
  void handleClient(int port) override;
};

#endif*/