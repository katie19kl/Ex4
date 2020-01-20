#ifndef _BFS_h_
#define _BFS_h_
#include "ISearcher.h"
#include "Searchable.h"
#include "State.h"
#include <queue>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

template <typename T, typename Solution>

class BFS : public ISearcher<T, Solution>
{
private:
    State<T> startFrom;

public:
    BFS(Searchable<T> *problem)
    {
        startFrom = problem->getInitState();
    }

    Solution search(Searchable<T> *searchableCopy) override
    {

        queue<State<T>> queueOfState;

        queueOfState.push(startFrom);
        State<T> workingState;
        State<T> *neighbour;
        vector<State<T> *> neighbourVec;
        pair<State<T>, double> pairFatherPrice;
        State<T> *solGet;
        int flagEnd = 0;
        while (!queueOfState.empty() && flagEnd == 0)
        {
            workingState = queueOfState.front();
            queueOfState.pop();
            neighbourVec = searchableCopy->getAllPossibleStates(workingState);

            for (int i = 0; i < neighbourVec.size(); i++) // traversing over shchenim
            {

                neighbour = neighbourVec.at(i);
                if (neighbour->statusVisit() == false)
                {
                    neighbour->setVisited();
                    neighbour->setPrevInPath(workingState);
                    queueOfState.push(*neighbour);
                }
                if (searchableCopy->isGoalState(*neighbour))
                {
                    solGet = neighbour;
                    flagEnd = 1;
                    break;
                }
            }
        }
        string path;
        double cost;
        int i = 0;

        while (solGet->getPrevState() != NULL)
        {
            i++;
            path += solGet->to_string() + to_string(int(solGet->getCost())) + "\n";
            cost += solGet->getCost();
            solGet = solGet->getPrevState();
        }

        path += solGet->to_string() + to_string(int(solGet->getCost())) + "\n";
        cost += solGet->getCost();

        cout << path << endl;
        cout << "length is" << i << endl;
        return "HUI";
    }
};
#endif
