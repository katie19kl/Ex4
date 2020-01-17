#include "Server.h"
#include <stdio.h>
//#include "ClientHandler.h"
#include <string>
#include "Solver.h"
#include "MySerialServer.h"
#include "CacheManager.h"
#include "SearcherAdapter.h"
#include "Matrix.h"
#include "FileCacheManager.h"
#include "CellMatrix.h"

using namespace std;

int main()
{
    int PORT = 8507;


    //Solver<Matrix, string> *solver = new SearcherAdapter <Matrix, string>();
    //CacheManager<Matrix,string>* cache = new FileCacheManager<Matrix,string>();


    //Server* server = new MySerialServer();
    //vector <string> s;

    //Searchable <CellMatrix> * Sear = new Matrix <CellMatrix>;

//    Sear->toString();        
    //solver->solve(m);
    cout<<"PART C"<<endl;

   
   // ClientHandler* clientHandler = new MyTestClientHandler(cache, solver);

    //server->open(PORT,clientHandler);

    return 0;
}