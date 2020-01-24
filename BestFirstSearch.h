//
// Created by katie on 21/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H_
#define EX4_BESTFIRSTSEARCH_H_

#include "Searcher.h"
#include "ISearcher.h"
#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T, typename Solution>

class BestFirstSearch : public Searcher<T, Solution>
{
private:
public:
    BestFirstSearch() = default;

    Solution search(Searchable<T> *searchableCopy) override
    {
        State<T> *finalState = NULL;
        State<T> *s; //specific successor
        vector<State<T> *> successors;
        auto *closed = new unordered_set<string>();
        auto *n = new State<T>;
        State<T> *initial;
        initial = searchableCopy->getInitState();
        vector<State<T> *> pathVec;

        initial->setCostInPath(initial->getCost());
        this->addToOpenList(*initial);

        while (this->getOpenListSize() > 0)
        {
            *n = this->popOpenList();
            closed->insert(n->getStateType().toString());

            if (searchableCopy->isGoalState(*n))
            {
                finalState = n;
                break;
            }

            successors = searchableCopy->getAllPossibleStates(*n);
            for (int i = 0; i < successors.size(); i++)
            {
                s = successors.at(i);

                if ((closed->find(s->getStateType().toString()) == closed->end()) && (!this->openListContains(*s)))
                {
                    s->setPrevInPath(*n);
                    s->setCostInPath(n->getCostInPath() + s->getCost());

                    this->addToOpenList(*s);
                }
                else if (n->getCostInPath() + s->getCost() < s->getCostInPath())
                {
                    //adjust cost
                    s->setCostInPath(n->getCostInPath() + s->getCost());
                    s->setPrevInPath(*n);

                    if (!this->openListContains(*s))
                    {

                        this->addToOpenList(*s);
                    }
                    else
                    {
                        this->adjustStatePriority(*s);
                    }
                }
            }

        } //found optimal path
// if no way exists
        if (finalState == NULL)
        {
            throw " no path was find";
        }

        cout << "total cost: " << finalState->getCostInPath() << endl;

        while (finalState->getPrevState() != NULL)
        {

            pathVec.insert(pathVec.begin(), finalState);
            cout << finalState->getStateType().toString() << "cost: " << finalState->getCostInPath() << endl;
            finalState = finalState->getPrevState();
        }
        pathVec.insert(pathVec.begin(), finalState);

        cout << "length is " << this->getNumberOfNodesEvaluated() << endl;
        return pathVec;
    }
};

#endif //EX4_PARTC_BESTFIRSTSEARCH_H_
