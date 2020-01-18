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
    //State <T> previous; /// CDF of cost 
public:

    State (){}

    State (int xOut, int yOut, double costParsed) : stateType (xOut, yOut, costParsed){   /// xOut,yOut num if cell && costParsed value in TXT
        this->cost = costParsed;
    }
    bool equals (State <T>& stateOutSide){
        return stateType.equalCheck(stateOutSide.getStateType());
    }
    T getStateType(){
        return stateType;
    }
    void setPrevState(State <T>& statePrev){
        this->previous = statePrev;
    }
    State <T> getPrevState(){
        return this->previous;
    }

    double getCost() {
        return this->cost;
    }
};

#endif