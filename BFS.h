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
    State<T> *startFrom;

public:
    BFS() = default;

    Solution search(Searchable<T> *searchableCopy) override
    {

        startFrom = searchableCopy->getInitState();
        queue<State<T>> queueOfState;

        vector<State<T> *> sol;

        queueOfState.push(*searchableCopy->getInitState());
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
// no way
        if (solGet == NULL)
        {
            throw " no path was find";
        }

        string path;
        double cost;
        int i = 0;

        while (solGet->getPrevState() != NULL)

        {
            sol.insert(sol.begin(), solGet);
            i++;
            path += solGet->to_string() + to_string(int(solGet->getCost())) + "\n";
            cost += solGet->getCost();
            solGet = solGet->getPrevState();
        }

        sol.insert(sol.begin(), solGet);
        path += solGet->to_string() + to_string(int(solGet->getCost())) + "\n";
        cost += solGet->getCost();

        cout << path << endl;
        cout << "length is" << i << endl;
        cout << "cost is: " << cost << endl;
        return sol;
    }
};
#endif
