#ifndef _SearcherAdapter_h_
#define _SearcherAdapter_h_
#include "Solver.h"
#include "Searchable.h"
#include "ISearcher.h"


template <typename Problem , typename Solution>


class SearcherAdapter : public Solver <Problem , Solution>
{
private:
/*
    ISearcher <Problem,Solution>* searcher;
    Searchable <Problem > * searchAble;*/

public:
    Solution solve(Problem & p){
        cout<<"SOLVING ADAPTER"<<endl;

        vector<State<CellMatrix>> vec;

        return vec;
    }
};


#endif