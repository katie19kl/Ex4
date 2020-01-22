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

template<typename T, typename Solution>

class BestFirstSearch: public Searcher<T, Solution> {
 private:
  State<T> startFrom;

 public:
  BestFirstSearch(Searchable<T>* problem) {
    //startFrom = problem->getInitState();
  }

  Solution search(Searchable<T> *searchableCopy) override {
      State<T> * finalState;
      State<T> * s; //specific successor
      vector<State<T> *> successors;
      auto * closed = new unordered_set<string>();
      State<T> * n;
      State<T> * initial;
      initial = searchableCopy->getInitState();

      initial->setCostInPath(initial->getCost());
      this->addToOpenList(*initial);
      //startFrom.setCostInPath(startFrom.getCost());
      //this->addToOpenList(startFrom);

      while (this->getOpenListSize() > 0) {
          *n = this->popOpenList();
          closed->insert(n->getStateType().toString());

          if (searchableCopy->isGoalState(*n)) {
            finalState = n;
            break;
          }

          successors = searchableCopy->getAllPossibleStates(*n);
          for (int i = 0; i < successors.size(); i++) {
              s = successors.at(i);

              if ((closed->find(s->getStateType().toString()) == closed->end()) && (!this->openListContains(*s))) {
                  s->setPrevInPath(*n);
                  s->setCostInPath(n->getCostInPath() + s->getCost());

                  this->addToOpenList(*s);

              } else if (n->getCostInPath() < s->getCostInPath()) {
                  //adjust cost
                  s->setCostInPath(n->getCostInPath() + s->getCost());
                  s->setPrevInPath(*n);

                  if (!this->openListContains(*s)) {

                      this->addToOpenList(*s);
                  } else {
                      this->adjustStatePriority(*s);
                  }
              }
          }

      } //found optimal path


      //taken from dimka's code, because it's useful
      string path;
      double cost = 0, i = 0;

      while (finalState->getPrevState() != NULL) {
          i++;
          path += finalState->to_string() + to_string(int(finalState->getCost())) + "\n";
          cost += finalState->getCost();
          finalState = finalState->getPrevState();
      }

      path += finalState->to_string() + to_string(int(finalState->getCost())) + "\n";
      cost += finalState->getCost();

      /*while (finalState->getPrevState() != NULL) {
          //cout << finalState->getStateType().toString() << "cost: " <<  << endl;
      }*/

      //cout << path << endl;
      cout << "total cost: " << finalState->getCostInPath() << endl;
      cout << "length is" << this->getNumberOfNodesEvaluated() << endl;
      return "bla";

  }


};

#endif //EX4_PARTC_BESTFIRSTSEARCH_H_
