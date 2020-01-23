#ifndef AStar_H_
#define AStar_H_

#include "Searcher.h"
#include "ISearcher.h"
#include <unordered_set>
#include <iostream>
#include <string>
#include <string>
#include <unordered_map>

using namespace std;

template <typename T, typename Solution>

class AStar : public Searcher<T, Solution>
{
    State<T> destState;
    int xEnd, yEnd;

public:
    AStar(Searchable<T> *copy)
    {
        this->destState = copy->getGoalState();
        xEnd = destState.getStateType().getX();
        yEnd = destState.getStateType().getY();
    }

    Solution search(Searchable<T> *searchableCopy) override
    {
        State<T> *solGet, *oneSuccessor, *m = new State<T>();
        State<T> *startState = searchableCopy->getInitState();
        vector<State<T> *> sol;

        startState->setCostInPath(0 + ManhattanDistance(*startState)); // g + h

        vector<State<T> *> successors;
        unordered_set<string> *closed = new unordered_set<string>();

        unordered_map<string, double> gState;
        gState[startState->to_string()] = 0;

        double cost, gStartState, hFuncState, tentative_gScore;
        string stateRepres;

        this->addToOpenList(*startState);

        while (this->getOpenListSize() > 0)
        {
            *m = this->topElementAStar();
            if (searchableCopy->isGoalState(*m))
            {
                solGet = m;
                break;
            }
            this->popOpenListAStar(); // lowest f

            successors = searchableCopy->getAllPossibleStates(*m);

            for (int i = 0; i < successors.size(); i++)
            {

                oneSuccessor = successors.at(i);
                tentative_gScore = gState.find(m->to_string())->second + oneSuccessor->getCost();

                bool infinity = false;
                if (gState.find(oneSuccessor->to_string()) == gState.end())
                {
                    infinity = true;
                }

                if (infinity || tentative_gScore < gState.find(oneSuccessor->to_string())->second)
                {

                    oneSuccessor->setPrevInPath(*m);

                    gState[oneSuccessor->to_string()] = tentative_gScore;

                    oneSuccessor->setCostInPath(tentative_gScore + ManhattanDistance(*oneSuccessor));

                    if (!this->openListContains(*oneSuccessor))
                    {
                        this->addToOpenList(*oneSuccessor);
                    }
                }
            }
        }

        string path;
        double cost_cost;
        int i = 0;
        // backtracing
        while (solGet->getPrevState() != NULL)
        {
            sol.insert(sol.begin(), solGet);
            i++;
            path += solGet->to_string() + to_string(int(solGet->getCost())) + "\n";
            cost_cost += solGet->getCost();
            solGet = solGet->getPrevState();
        }

        path += solGet->to_string() + to_string(int(solGet->getCost())) + "\n";
        cost_cost += solGet->getCost();

        sol.insert(sol.begin(), solGet);

        // Maybe minus one // extra nodes
        cout << path << endl;
        int numStatesEvaluated = this->getNumberOfNodesEvaluated() - 1;
        cout << "length is" << numStatesEvaluated << endl;

        this->setNumberOfNodes(numStatesEvaluated);

        return sol;
    }

    // Heiristic for up/down/left/right
    double ManhattanDistance(State<T> curr)
    {
        double h;
        h = abs(curr.getStateType().getX() - xEnd) + abs(curr.getStateType().getY() - yEnd);
        return h;
    }
};

#endif
