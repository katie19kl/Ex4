#ifndef _Searchable_h_
#define _Searchable_h_
#include "State.h"
#include <vector>
#include "CellMatrix.h"

template <typename T>

class Searchable
{
 protected:
  State<T> curPos;
  State<T>* initPos;
  State<T> destPos;

 public:

  virtual State<T>* getInitState() = 0;

  virtual State<T> getGoalState() = 0;

  virtual bool isGoalState(State<T>&) = 0;

  virtual std::vector<State<T>*> getAllPossibleStates(State<T>&) = 0;

  virtual string toString() = 0;


};

#endif