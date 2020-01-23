#ifndef _SearcherAdapter_h_
#define _SearcherAdapter_h_
#include "Solver.h"
#include "Searchable.h"
#include "ISearcher.h"


template <typename Problem , typename Solution, typename T>

class SearcherAdapter : public Solver <Problem , Solution, T>
{
private:
    ISearcher <T, Solution>* searcher;

public:
  Solution solve(Problem &p){

      vector<State<CellMatrix>*> vec;
      return vec;
  }

  void SetSearcher(ISearcher<T , Solution>* searcher1) {
      this->searcher = searcher1;
  }

  Solution solve(Problem *p){
      cout<<"SOLVING ADAPTER"<<endl;
      return searcher->search(p); //returns a vector<State<T> *> of all the states of cell matrices in the path
  }
};


#endif