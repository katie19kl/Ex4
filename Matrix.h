#ifndef _Matrix_h_
#define _Matrix_h_

#include "CellMatrix.h"
#include <string>
#include "Searchable.h"
#include "vector"
#include "State.h"
using namespace std;

template <typename T> // T == CellMatrix

class Matrix : public Searchable<T>
{
private:
    int numRows = 5;
    int numColum = 5;
    State<T> **representation;
    

public:
   /* Matrix(vector<string> parsed)
    {
      //  fullFillFields(parsed); ////
        
        In this class
        1- update numRows and numColum
        2- update representation
        ----
        Update 3 fields of super class!! via setters cauze we have default constructo => creates empty super class + activate 3 setters.
        
    }
    */
    string toString()// we have access to each item in matrix (both cost and indexes)
    {
        for (int i = 0; i < numColum; i++)
        {
            for (int j = 0; j < numRows; j++)
            {
                cout<<representation[j][i].getStateType().getX()<<endl;
                cout<<representation[j][i].getStateType().getY()<<endl; ///
            }
        }
        return "XUI";
    }
/*
    void fullFillFields(vector<string> parsed)
    { // KETI MAKES
    }*/

    State<T> getInitState() override
    {
        return this->initPos;
    }

    State<T> getGoalState() override
    {
        return this->destPos;
    }

    bool isGoalState(State<T> &stateToCheck) override
    {
        return this->destPos.getStateType().equalCheck(stateToCheck.getStateType());
    }

    vector<State<T>> getAllPossibleStates(State<T> &overItCheck)
    {
        int xOverCheck = overItCheck.getStateType().getX();
        int yOverCheck = overItCheck.getStateType().getY();
        vector<State<T>> vecSteps;
        // 8 ifim
        if (xOverCheck == 0 && yOverCheck == 0)
        {
            State<T> goRight = *(*(representation + 1));
            State<T> goDown = *(*(representation) + 1); // arr[1][0]
            vecSteps.emplace_back(goRight);
            vecSteps.emplace_back(goDown);
            return vecSteps;
        }
        return vecSteps;
    }
};

#endif