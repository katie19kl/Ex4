#include "Server.h"
#include <stdio.h>
#include <string>
#include "Solver.h"
#include "MySerialServer.h"
#include "CacheManager.h"
#include "SearcherAdapter.h"
#include "Matrix.h"
#include "FileCacheManager.h"
#include "CellMatrix.h"
#include "MyClientSearchClientHandler.h"

using namespace std;

int main()
{
    int PORT = 12345;


    Solver<Matrix<CellMatrix>, vector<State<CellMatrix>>> *solver = new SearcherAdapter <Matrix<CellMatrix>, vector<State<CellMatrix>>>();
    
    CacheManager<Matrix<CellMatrix>,vector<State<CellMatrix>>>* cache = new FileCacheManager<Matrix<CellMatrix>,vector<State<CellMatrix>>>();

    Server* server = new MySerialServer();

    //cout<<"PART C"<<endl;

   
    ClientHandler* clientHandler = new MyClientSearchClientHandler(cache, solver);

    server->open(PORT,clientHandler);

    return 0;
}