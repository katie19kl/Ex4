#include "MyClientSearchClientHandler.h"
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>

void updateVec(string fromBuffer, vector<string> * parsed);


void MyClientSearchClientHandler :: handleClient(int port)
{
    auto *vectorStrings = new vector<string>();

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
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
    tv.tv_sec = 60; //1 minutes
    tv.tv_usec = 0;
    cout << "here--0" << endl;
    char *actText;
    // accepting a client
    while (true)
    {
        // accepting a client
        int flagT = 1;

        if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,
                       sizeof(tv)) < 0)
            ;

        int client_socket = accept(socketfd, (struct sockaddr *)&address, (socklen_t *)&address);

        cout << "here--1" << endl;
        if (client_socket == -1)
        {
            std::cerr << "Error accepting client" << std::endl;
            return;
        }

        try
        {
            setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv);
            char buffer[2048];
            while (read(client_socket, buffer, 2048)) //while data is transferred
            {
                string s(buffer);
                updateVec(s, vectorStrings); // read string till /n
                if (s.find("end") != string::npos) {
                    break;
                }
            }

            if (vectorStrings->size() <= 3) {
                throw "Error - the input in the txt file is invalid"; //supposed to be more than 3 strings
            }

            //create matrix problem
            Matrix<CellMatrix> matrix(vectorStrings);
            vector<State<CellMatrix>> solution;

            cout << "problem is " << matrix.toString() << endl;
            
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


            //send(client_socket, solutionArr, strlen(solutionArr), 0);

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
}

void updateVec(string fromBuffer, vector<string> * parsed)
{
    int i = 0, j = 0;
    string currentLine;

    while (i < fromBuffer.length())
    {
        if (fromBuffer[i] == ' ') {
            i++; //get rid of unnecessary spaces
            continue;
        }
        if (fromBuffer[i] == '\n') {
            parsed->emplace_back(fromBuffer.substr(j, i - j));
            j = i + 1;
        }
        i++;
    }
}