#ifndef _DFS_h_
#define _DFS_h_
#include "ISearcher.h"
#include "Searchable.h"
#include "State.h"

using namespace std;

template <typename T, typename Solution>

class DFS : public ISearcher<T, Solution>
{
private:
    State<T> startFrom;

public:
    DFS(Searchable<T> *problem)
    {
        startFrom = problem->getInitState();
    }

    Solution search(Searchable<T> *searchableCopy) override
    {
        // have to make only DFS visit
        State<T> *solGet;
        dfsVisit(searchableCopy, &startFrom, solGet);
        cout << "here" << endl;
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

    void dfsVisit(Searchable<T> *searchableCopy, State<T> *stateRun, State<T> *&solGet)
    {
        State<T> *neighbour;
        stateRun->setVisited();
        vector<State<T> *> neighbours = searchableCopy->getAllPossibleStates(*stateRun); //may be save po another

        int randIndex = rand() % neighbours.size();
        int startIndex = randIndex, flagFinish = 0;

        for (int i = randIndex; i < neighbours.size(); i++) /// Random
        //for (int i = 0; i < neighbours.size(); i++) /// Ikvi

        {

            neighbour = neighbours.at(i);
            if (neighbour->statusVisit() == false)
            {

                neighbour->setPrevInPath(*stateRun);

                dfsVisit(searchableCopy, neighbour, solGet);
            }
            if (searchableCopy->isGoalState(*neighbour))
            {
                flagFinish = 1;
                solGet = neighbour;
                //solGet = new State<T>(*neighbour);
                return;
            }
        }

        if (flagFinish == 0)
            for (int i = 0; i < randIndex; i++)
            {
                neighbour = neighbours.at(i);
                if (neighbour->statusVisit() == false)
                {

                    neighbour->setPrevInPath(*stateRun);

                    dfsVisit(searchableCopy, neighbour, solGet);
                }
                if (searchableCopy->isGoalState(*neighbour))
                {
                    flagFinish = 1;
                    solGet = neighbour;
                    //solGet = new State<T>(*neighbour);
                    return;
                }
            }
        return;
    }
};

#endif