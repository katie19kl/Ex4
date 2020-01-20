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

        State<T> currPos = searchableCopy->getInitState();

        queue<State<T>> queueOfState;

//        unordered_map< pair<int,int>, pair<State<T>, double>> sonFather_Price; 

        queueOfState.push(startFrom);

        State<T> workingState;
        vector<State<T>> neighbours;
        pair<State<T>, double> pairFatherPrice;

        while (!queueOfState.empty())
        {
            workingState = queueOfState.front();
            queueOfState.pop();
            neighbours = searchableCopy->getAllPossibleStates(workingState);

            for (int i = 0; i < neighbours.size(); i++) // traversing over shchenim
            {

                State <T> * f = new State<T> (workingState);
                cout << " From state to ointer was done"<<endl;

                neighbours.at(i).setPrevInPath(workingState);

                State<T> * neigbour = &workingState;
                
                
                if (searchableCopy->isGoalState(neighbours.at(i)))
                {

                    break;
                }
            }
        }

        return "HUI";
    }
};
#endif
