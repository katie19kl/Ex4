#ifndef _Matrix_h_
#define _Matrix_h_

#include "Searchable.h"
#include "CellMatrix.h"
#include <string>
#include <iostream>
#include <sstream>
#include "vector"
#include "State.h"
using namespace std;

template <typename T> // T == CellMatrix

class Matrix : public Searchable<T>
{
private:
    int numRows;
    int numColumn; //did refactor
    State<T> **representation;


public:
    Matrix(vector<string>*  parsed)
    {

        fullFillFields(parsed);
        
        /*In this class
        1- update numRows and numColumn
        2- update representation
        ----
        Update 3 fields of super class!! via setters cauze we have default constructor => creates empty super class + activate 3 setters.
        */
    }

    string toString()// we have access to each item in matrix (both cost and indexes)
    {
        string stringRep = "";

        for (int i = 0; i < numColumn; i++)
        {
            for (int j = 0; j < numRows; j++)
            {
                stringRep += string("(") + to_string(representation[j][i].getStateType().getX()) + string(", ")
                    + to_string(representation[j][i].getStateType().getY()) + string(") : cost: ")
                    + to_string(representation[j][i].getCost())
                    + string(", ");
            }
        }
        return stringRep;
    }

    void fullFillFields(vector<string>* parsed) {
        string startP, endP, cost, updatedCost, intermediate;
        int numComa = 0, k, l;
        double actualCost;
        size_t sz;

        while (parsed->back() != "end") {
            parsed->pop_back();
        }
        if (parsed->back() == "end") {
            parsed->pop_back();
            endP = parsed->back();
            parsed->pop_back();
            startP = parsed->back();
            parsed->pop_back();

            //now we have the matrix represented with strings
            numRows = parsed->size();
            for (char c: parsed->at(0)) {

                if (c == ',') {
                    numComa++;
                }
            }
            numColumn = numComa + 1;

            representation = new State<T>*[numRows];
            for (int i = 0; i < numRows; i++) { //going over y values
                representation[i] = new State<T>[numColumn];
                k = 0, l = 0; //used for iterating over the chars in a string representation of a specific matrix line
                for (int j = 0; j < numColumn; j++) { //going over x values
                    while (parsed->at(i)[k] != ',') {
                        k++;
                    } //k on ','
                    cost = parsed->at(i).substr(l, k - l);

                    //removing spaces
                    stringstream check1(cost);
                    while(getline(check1, intermediate, ' ')) {
                        updatedCost += intermediate;
                    }

                    actualCost = stod(updatedCost, &sz);
                    updatedCost = "", cost = "", intermediate = "";
                    cout << "x value: " << j << ", y value: " << i << " cost: " << actualCost << endl;

                    representation[j + numRows * i] = new State<T>(j, i, actualCost);
                    k++;
                    l = k;
                }
            }

            setFieldsSearchable(startP, endP); //setting the fields defined in Searchable
        }
    }

    State<T> getInitState() override
    {
        return this->initPos;
    }

    vector<State<T>> getGoalState() override
    {
        vector<State<T>> goalStates;

        goalStates.emplace_back(this->destPos);
        return goalStates;
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

    void setFieldsSearchable(const string& start, const string& end) {
        string intermediate, updatedStr, left, right;
        int xVal, yVal, j = 0;
        double costVal;

        //setting initial state
        stringstream check1(start);
        while(getline(check1, intermediate, ' ')) {
            updatedStr += intermediate;
        }

        while (updatedStr[j] != ',') {
            left += updatedStr[j]; //creating the x value of the point
            j++;
        } //j on ','

        right = updatedStr.substr(j + 1, updatedStr.length() - (j + 1)); //y value of the point

        //converting the x and y values (represented with strings) to ints
        stringstream leftNum(left);
        leftNum >> xVal;
        stringstream rightNum(right);
        rightNum >> yVal;

        State<T> stateInit(xVal, yVal, representation[xVal][yVal].getCost());
        setInitPos(stateInit);
        setCurPos(stateInit);

        //now setting the goal state
        updatedStr = "" , left = "", right = "", intermediate = "";

        stringstream check2(end);
        while(getline(check2, intermediate, ' ')) {
            updatedStr += intermediate;
        }

        j = 0;
        while (updatedStr[j] != ',') {
            left += updatedStr[j]; //creating the x value of the point
            j++;
        } //j on ','

        right = updatedStr.substr(j + 1, updatedStr.length() - (j + 1)); //y value of the point

        //converting the x and y values (represented with strings) to ints
        stringstream leftNumEnd(left);
        leftNum >> xVal;
        stringstream rightNumEnd(right);
        rightNum >> yVal;

        State<T> stateGoal(xVal, yVal, representation[xVal][yVal].getCost());
        setDestPos(stateGoal);
    }

    void setCurPos(State<T> current) {
        this->curPos = current;
    }

    void setInitPos(State<T> initial) {
        this->initPos = initial;
    }

    void setDestPos(State<T> dest) {
        this->destPos = dest;
    }
};

#endif