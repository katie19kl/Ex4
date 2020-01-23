
#ifndef _Searcher_h_
#define _Searcher_h_

#include "Searchable.h"
#include "ISearcher.h"
#include <queue>
#include <string>
#include <algorithm>
#include "compareStates.h"
#include "MyPriorityQueue.h"
#include "CellMatrix.h"
#include "State.h"

template <typename T, typename Solution>

class Searcher : public ISearcher<T, Solution>
{
private: // Members to BeastFS and A*
    MyPriorityQueue<T> openList;
    int evaluatedNodes;

protected:
    
  State<T> popOpenList() {
      evaluatedNodes++;
      State<T> topState;
      topState = openList.top();
      openList.pop();
      return topState;
  }
    void popOpenListAStar()
    {
        evaluatedNodes++;
        openList.pop();
    }

    State<T> topElementAStar()
    {

        //evaluatedNodes++;
        return openList.top();
    }

    void removeFromQueue(const State<T> &state)
    {
        openList.remove(state);
    }

    void addToOpenList(const State<T> &state)
    {
        openList.push(state);
    }

    void adjustStatePriority(const State<T> &state)
    {
        openList.remove(state);
        openList.push(state);
    }

public:
    Searcher()
    {
        evaluatedNodes = 0;
    }

    Solution search(Searchable<T> *searchable) = 0;

    State<T> getTopState()
    {
        State<T> toRet = openList.top();
        return toRet;
    }

    int getOpenListSize()
    {
        return openList.size();
    }

    int getNumberOfNodesEvaluated()
    {
        return evaluatedNodes;
    }

    void setNumberOfNodes(int i ){
        this->evaluatedNodes = i;
    }

    bool openListContains(State<T> state)
    {
        vector<string> statesInPQ;
        MyPriorityQueue<T> temp = this->openList;
        bool isInPQ = false;

        while (!temp.empty())
        { //adding all states in the openList to a vector of states
            string currState = temp.top().getStateType().toString();
            statesInPQ.emplace_back(currState);
            temp.pop();
        }

        //now we can traverse all the states to find out if the state is in the priority queue
        for (unsigned long i = 0; i < statesInPQ.size(); i++)
        {
            if (statesInPQ.at(i) == state.getStateType().toString())
            {
                isInPQ = true;
                break;
            }
        }

        return isInPQ;
    }
};

#endif