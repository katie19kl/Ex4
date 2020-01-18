#ifndef _MyClientSearchClientHandler_h
#define _MyClientSearchClientHandler_h
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

  CacheManager<Matrix<CellMatrix>, vector<State<CellMatrix>>> *cache;
  Solver<Matrix<CellMatrix>, vector<State<CellMatrix>>> *solver;

public:
  MyClientSearchClientHandler(CacheManager<Matrix<CellMatrix>, vector<State<CellMatrix>>> *cache_manager,
      Solver<Matrix<CellMatrix>, vector<State<CellMatrix>>> *problem_solver)
  {

    this->cache = cache_manager;
    this->solver = problem_solver;
  }
  void handleClient(int port) override;
};

#endif