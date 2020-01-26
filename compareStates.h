//
// Created by katie on 21/01/2020.
//

#ifndef EX4_PARTC_COMPARESTATES_H_
#define EX4_PARTC_COMPARESTATES_H_

#include "State.h"

template <typename T>

struct compareStates {

  bool operator()(const State<T>& state1, const State<T>& state2) {
      return state1.getCostInPath() > state2.getCostInPath();
  }

};

#endif //EX4_PARTC_COMPARESTATES_H_
