#include "Server.h"
#include "MyTestClientHandler.h"
#include <stdio.h>
#include "MySerialServer.h"
#include "ClientHandler.h"
#include <string>
#include "Solver.h"
#include "CacheManager.h"
#include "StringReverseAdapter.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "String.h"
using namespace std;

int main()
{
    int PORT = 8507;


    StringReverser strReverser;
    String str;
    Solver<String, string> *solver = new StringReverseAdapter<String, string>();

    Server* server = new MySerialServer();

    CacheManager<String,string>* cache = new FileCacheManager<String,string>();

    ClientHandler* clientHandler = new MyTestClientHandler(cache, solver);

    server->open(PORT,clientHandler);

    return 0;
}