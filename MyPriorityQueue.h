//
// Created by katie on 21/01/2020.
//

#ifndef EX4_PARTC_MYPRIORITYQUEUE_H_
#define EX4_PARTC_MYPRIORITYQUEUE_H_

#include <queue>
#include <vector>
#include <algorithm>
#include "compareStates.h"
#include "State.h"

using namespace std;

template <typename T>


class MyPriorityQueue: public priority_queue<State<T>, vector<State<T>>, compareStates<T>>  {

 public:
  MyPriorityQueue() = default;

  bool remove(State <T> value) {
      auto it = std::find(this->c.begin(), this->c.end(), value);

      if (it != this->c.end()) {
          this->c.erase(it);
          make_heap(this->c.begin(), this->c.end(), this->comp);

          return true;
      } else {
          return false;
      }
  }


};

#endif //EX4_PARTC_MYPRIORITYQUEUE_H_
