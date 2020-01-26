#include "MyClientSearchClientHandler.h"
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <algorithm>
#include "Searchable.h"
#include "DFS.h"
#include "CellMatrix.h"
#include "AStar.h"

using namespace std;

void updateVec(string fromBuffer, vector<string> *parsed);

string createStringSolution(const vector<State <CellMatrix> *>& statesInPath);

void MyClientSearchClientHandler :: handleClient(int client_socket) //change to socket
{
    auto *vectorStrings = new vector<string>(); //for matrix

    auto *vectorStringsToStore = new vector<string>(); //for matrix to store

    try
    {
        int flagFound = 0; // flag for end being read in the buffer
        string matrixStr = "";
        size_t posEndWord; //position of the "end" in the string
        char buffer[512];

        while (true) //while data is transferred
        {
            read(client_socket, buffer, 511);
            string s;

            for (int i = 0; i < 511; i++) //copying buffer content to a string
            {
                if (buffer[i] == '\0')
                {
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
            {
                break;
            }

            memset(buffer, 0, 511); //clear buffer
        }
        updateVec(matrixStr, vectorStrings); // read string till /n

        if (vectorStrings->size() <= 3)
        {
            throw "Error - the input in the txt file is invalid"; //supposed to be more than 3 strings
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////
        for (unsigned long i = 0; i < vectorStrings->size(); i++)
        {
            vectorStringsToStore->emplace_back(vectorStrings->at(i));
        }

        //will be stored in cache(a file)
        auto *searchableToStore = new Matrix<CellMatrix>(vectorStringsToStore);

        auto *searchable = new Matrix<CellMatrix>(vectorStrings);

        vector<State<CellMatrix>> solution;

        ISearcher<CellMatrix, vector<State<CellMatrix> *>> *searcher =
            new AStar<CellMatrix, vector<State<CellMatrix> *>>(searchable);

        this->solver->SetSearcher(searcher); //defining the concrete searcher(A Star - according to our experiment)

        try
        {

            string solutionInString;
            vector<State<CellMatrix> *> solutionInVec;
            const char *solutionToSend;

            if (this->cache->existSolution(searchableToStore))
            {
                solutionInString = this->cache->getSolution(searchableToStore);
            }
            else
            {
                solutionInVec = this->solver->solve(searchableToStore);
                solutionInString = createStringSolution(solutionInVec);
                this->cache->addSolutionToBase(solutionInString, searchableToStore);
            }

            solutionToSend = solutionInString.c_str(); //convert to an array

            send(client_socket, solutionToSend, strlen(solutionToSend), 0); //send solution to client

        } catch (const char *str)
        {
            const void *solutionArr = "Sorry, there is no way to get to the destination\n";
            send(client_socket, solutionArr, 71, 0);
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////
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

string createStringSolution(const vector<State <CellMatrix> *>& statesInPath) {
    string solution = "";
    int currentX, currentY, prevX, prevY;
    int cost = statesInPath.at(0)->getCost(); //the cost of the initial state

    //starting from second state
    for (unsigned long i = 1; i < statesInPath.size(); i++) {
        currentX = statesInPath.at(i)->getStateType().getX();
        currentY = statesInPath.at(i)->getStateType().getY();
        prevX = statesInPath.at(i)->getPrevState()->getStateType().getX();
        prevY = statesInPath.at(i)->getPrevState()->getStateType().getY();

        cost += statesInPath.at(i)->getCost();

        if (currentX == prevX + 1) {
            solution += "Right (" + to_string(cost) + "), ";

        } else if (currentX + 1 == prevX) {
            solution += "Left (" + to_string(cost) + "), ";

        } else if (currentY == prevY + 1) {
            solution += "Down (" + to_string(cost) + "), ";

        } else if (currentY + 1 == prevY) {
            solution += "Up (" + to_string(cost) + "), ";

        }
    }

    solution = solution.substr(0, solution.length() - 2); //removing the ", " in the end

    return solution;
}