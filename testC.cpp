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

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int PORT = stoi(argv[1]);

        Server *serverParallel = new ParallelServer();
        serverParallel->openParallel(PORT);
    }else {
        throw "To many arguments";
    }
    return 0;
}