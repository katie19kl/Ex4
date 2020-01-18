#ifndef _SearcherAdapter_h_
#define _SearcherAdapter_h_
#include "Solver.h"
#include "Searchable.h"
#include "Searcher.h"


template <typename Problem,typename Solution>


class SearcherAdapter : public Solver <Problem, Solution>
{
private:
    //Searcher* searcher;
    //Searchable* searchAble;

public:
    Solution solve(Problem& p){
        cout<<"SOLVING ADAPTER"<<endl;

        vector<State<CellMatrix>> vec;

        return vec;
    }
};


#endif