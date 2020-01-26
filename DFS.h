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
    State<T> *startFrom;
    int numNodesEvaluated;

public:
    DFS() = default;

    Solution search(Searchable<T> *searchableCopy) override
    {

        vector<State<T> *> sol;
        // have to make only DFS visit
        startFrom = searchableCopy->getInitState();
        this->numNodesEvaluated++;

        State<T> *solGet = NULL;
        dfsVisit(searchableCopy, startFrom, solGet);
        string path;
        double cost = 0;
        int i = 0;

        // no way
        if (solGet == NULL)
        {
            throw " no path was found";
        }
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

        return sol;
    }

    void dfsVisit(Searchable<T> *searchableCopy, State<T> *stateRun, State<T> *&solGet)
    {
        State<T> *neighbour;
        stateRun->setVisited();
        vector<State<T> *> neighbours = searchableCopy->getAllPossibleStates(*stateRun); //may be save po another

        this->numNodesEvaluated += neighbours.size();

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
                    return;
                }
            }
        return;
    }

    int getTotalNumOfNodes() {
        return this->numNodesEvaluated;
    }
};

#endif
