#include "MyClientSearchClientHandler.h"
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <algorithm>
#include "BFS.h"
#include "Searchable.h"
#include "DFS.h"
#include "Searcher.h"
#include "BestFirstSearch.h"
#include "CellMatrix.h"
#include "AStar.h"

using namespace std;

void updateVec(string fromBuffer, vector<string> *parsed);

void MyClientSearchClientHandler ::handleClient(int client_socket) //change to socket
{
    auto *vectorStrings = new vector<string>();

    auto *vectorStringsToStore = new vector<string>();

    /*int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        std::cerr << "Could not create a socket" << std::endl;
        return;
    }
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return;
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1)
    { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return;
    }

    struct timeval tv;
    tv.tv_sec = 600; //1 minutes
    tv.tv_usec = 0;
    cout << "here--0" << endl;
    char *actText;
    // accepting a client
    /////////////////////////////////////////////////outside
    while (true)
    {
        // accepting a client
        int flagT = 1;

        if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,
                       sizeof(tv)) < 0)
            ;

        int client_socket = accept(socketfd, (struct sockaddr *)&address, (socklen_t *)&address);//handling

        cout << "here--1" << endl;
        if (client_socket == -1)
        {
            std::cerr << "Error accepting client" << std::endl;
            return;
        }*/

    try
    {
        int flagFound = 0;
        string matrixStr = "";
        size_t posEndWord;
        //setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv);
        char buffer[512];
        while (true) //while data is transferred
        {
            read(client_socket, buffer, 511);
            //string s(buffer);
            string s;



            for (int i = 0; i < 511; i++)
            {
                if (buffer[i] == '\0'){
                    break;
                }
                s.push_back(buffer[i]);
            }



            if (s.find("end") != string::npos)
            {
                posEndWord = s.find("end");
                s = s.substr(0, posEndWord + strlen("end\n"));
                flagFound = 1;
            }


            matrixStr += s;
            if (flagFound)
            //if (s.find("end") != string::npos)
            {
                //cout << matrixStr << endl;
                break;
            }

            memset(buffer, 0, 511);
        }
        updateVec(matrixStr, vectorStrings); // read string till /n

        cout << "right here" << endl;
        if (vectorStrings->size() <= 3)
        {
            throw "Error - the input in the txt file is invalid"; //supposed to be more than 3 strings
        }
        cout << "after here" << endl;

        /////////////////////////////////////////////////////////////////////////////////////////////////////
        for (int i = 0; i < vectorStrings->size(); i++)
        {
            vectorStringsToStore->emplace_back(vectorStrings->at(i));
        }

        Searchable<CellMatrix> *searchableToStore = new Matrix<CellMatrix>(vectorStringsToStore);

        cout << "between matrices" << endl;
        Matrix<CellMatrix> *searchable = new Matrix<CellMatrix>(vectorStrings);

        vector<State<CellMatrix>> solution;
        //cout << "problem is " << searchable->toString() << endl;

        //ISearcher<CellMatrix, string> *searcher = new BFS<CellMatrix, string>();
        //ISearcher<CellMatrix, string> *searcher = new DFS<CellMatrix, string>();

        ISearcher<CellMatrix, vector<State<CellMatrix> *>> *searcher =
            new AStar<CellMatrix, vector<State<CellMatrix> *>>(searchable);

        this->solver->SetSearcher(searcher);
        vector<State<CellMatrix> *> solutionGET = this->solver->solve(searchable);

        /////////////////////////////////////////////////////////////////////////////////////////////////////

        /*
            if (this->cache->existSolution(matrix))
            {
                solution = this->cache->getSolution(matrix);
                cout << "Solution exists" << endl;
            }
            else
            {
                solution = this->solver->solve(matrix);
                this->cache->addSolutionToBase(solution, matrix);
            }
            */

        const void *solutionArr = "bla";
        send(client_socket, solutionArr, 5, 0);
    }
    catch (exception &e)
    {
        if (client_socket != -1)
        {
            close(client_socket);
            exit(1);
        }
    }
}

void updateVec(string fromBuffer, vector<string> *parsed)
{
    int i = 0, j = 0;
    string currentLine;

    int bufSize = fromBuffer.length();

    while (i < bufSize)
    {
        if (fromBuffer[i] == ' ')
        {
            i++; //get rid of unnecessary spaces
            continue;
        }
        if (fromBuffer[i] == '\n')
        {
            parsed->emplace_back(fromBuffer.substr(j, i - j));
            j = i + 1;
        }
        i++;
    }
}