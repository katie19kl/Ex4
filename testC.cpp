#include "Server.h"
#include <string>
#include "ParallelServer.h"

using namespace std;
using namespace server_side;

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int PORT = stoi(argv[1]);

        server_side::Server* serverParallel = new ParallelServer();
        serverParallel->openParallel(PORT);

    } else {
        throw "Too many arguments";
    }
    return 0;
}