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



  /*// we are doing operator overloading through this
  template<> bool operator> (const State<T>& s1, const State<T>& s2){
      return s1.getCost() > s2.getCost();
  }*/
};

#endif //EX4_PARTC_COMPARESTATES_H_
