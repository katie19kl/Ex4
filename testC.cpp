#include "Server.h"
#include <stdio.h>
#include "ClientHandler.h"
#include <string>
#include "Solver.h"
#include "MySerialServer.h"
#include "CacheManager.h"
#include "SearcherAdapter.h"
#include "Matrix.h"
using namespace std;

int main()
{
    int PORT = 8507;


    Solver<Matrix, string> *solver = new SearcherAdapter <Matrix, string>();

    Server* server = new MySerialServer();
    Matrix m;
    
    solver->solve(m);
    cout<<"PART C"<<endl;

    //CacheManager<String,string>* cache = new FileCacheManager<String,string>();

   // ClientHandler* clientHandler = new MyTestClientHandler(cache, solver);

    //server->open(PORT,clientHandler);

    return 0;
}