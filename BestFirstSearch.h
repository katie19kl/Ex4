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
    startFrom = problem->getInitState();
  }

  Solution search(Searchable<T> *searchableCopy) override {
      State<T> * finalState;
      State<T> * s; //specific successor
      vector<State<T> *> successors;

      State<T> initial  = searchableCopy->getInitState();
      this->addToOpenList(initial);
      auto * closed = new unordered_set<string>();
      State<T> * n;

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
                  this->addToOpenList(*s);

              } else if (s->getCost() < this->getTopState().getCost()) {

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

      cout << path << endl;
      cout << "length is" << i << endl;
      return "bla";

  }


};

#endif //EX4_PARTC_BESTFIRSTSEARCH_H_
