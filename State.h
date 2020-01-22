#ifndef _State_h_
#define _State_h_


#include "State.h"
using namespace std;

template <typename T>  // T == CellMatrix

class State
{
private:
    T stateType;
    double cost;
    bool wasVisited;
    State <T> *previous; /// CDF of cost 
public:

    State (){previous = NULL;}

    State (int xOut, int yOut, double costParsed) : stateType (xOut, yOut, costParsed){   /// xOut,yOut num if cell && costParsed value in TXT
        this->cost = costParsed;
        wasVisited = false;
        previous = NULL;
    }
    bool equals (State <T>& stateOutSide){
        return stateType.equalCheck(stateOutSide.getStateType());
    }
    T getStateType() const {
        return stateType;
    }
    void setPrevState(State <T>& statePrev){
        this->previous = statePrev;
    }
    State <T>* getPrevState(){
        return this->previous;
    }

    double getCost() const {
        return this->cost;
    }
    void setPrevInPath(State <T> prev){
        State <T> * toPut = new State<T> (prev);
        this->previous = toPut;
    }

    bool statusVisit(){
        return this->wasVisited;
    }
    void setVisited(){
        this->wasVisited = true;
    }
    void setUn_Visited(){
        this->wasVisited = false;
    }

    string to_string(){
        return this->stateType.toString();
    }


    bool operator<(const State<T>& s1) const {
        return getCost() < s1.getCost();
    }

};

#endif