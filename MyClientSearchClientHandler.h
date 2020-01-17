#ifndef _MyClientSearchClientHandler_h
#define _MyClientSearchClientHandler_h_
#include "ClientHandler.h"
#include <string>
#include "Solver.h"
#include "CacheManager.h"
#include "Matrix.h"

using namespace std;
class MyClientSearchClientHandler : ClientHandler
{
private:
  CacheManager<Matrix, string> * cache;
  Solver<Matrix, string> * solver;

public:

};


#endif