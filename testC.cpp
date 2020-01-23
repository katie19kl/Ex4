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
#include "ParallelServer.h"

using namespace std;

int main()
{
    int PORT = 12345;


    Server* serverParallel = new ParallelServer();
    //cout<<"PART C"<<endl;


    serverParallel->openParallel(PORT);

    return 0;
}