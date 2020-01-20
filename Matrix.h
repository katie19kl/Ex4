#ifndef _Matrix_h_
#define _Matrix_h_

#include <fstream>
#include "Searchable.h"
#include "CellMatrix.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "vector"
#include "State.h"
using namespace std;

template <typename T> // T == CellMatrix

class Matrix : public Searchable<T>
{
 private:
  int numRows;
  int numColumn;
  State<T> **representation;

 public:
  Matrix(vector<string> *parsed)
  {

      fullFillFields(parsed);
  }

  string toString() // we have access to each item in matrix (both cost and indexes)
  {
      string stringRep = "";

      for (int i = 0; i < numColumn; i++)
      {
          for (int j = 0; j < numRows; j++)
          {
              stringRep += string("(") + to_string(representation[i][j].getStateType().getX())
                  + string(", ") + to_string(representation[i][j].getStateType().getY()) /*+ string(") : cost: ")*/
                  + ")" + to_string(int(representation[i][j].getCost())) + string(", ");
          }
          stringRep += "\n";

          stringRep += "---------------------------------------";

          stringRep += "\n";
      }
      stringRep += "GOAL IS \n";
      stringRep += to_string(this->getGoalState().at(0).getStateType().getX());
      stringRep += to_string(this->getGoalState().at(0).getStateType().getY());

      stringRep += "INIT IS \n";
      stringRep += to_string(this->getInitState().getStateType().getX());
      stringRep += to_string(this->getInitState().getStateType().getY());

      ofstream outfile;
      outfile.open("MATRIX.TXT");
      // write inputted data into the file.
      outfile << stringRep << endl;
      // close the opened file.
      outfile.close();

      return stringRep;
  }

  void fullFillFields(vector<string> *parsed)
  {
      string startP, endP, cost, updatedCost;
      int numComa = 0, k, l;
      double actualCost;
      size_t sz;

      while (parsed->back() != "end")
      {
          parsed->pop_back();
      }
      if (parsed->back() == "end") // removing start and end point
      {
          parsed->pop_back();
          endP = parsed->back();
          parsed->pop_back();
          startP = parsed->back();
          parsed->pop_back();

          cout << "here " << endl;
          for (int i = 0; i < parsed->size(); i++)
          {
              parsed->at(i).erase(remove_if(parsed->at(i).begin(), parsed->at(i).end(),
                                            [](char c) {
                                              return (c == ' ');
                                            }),
                                  parsed->at(i).end());
          }

          //now we have the matrix represented with strings
          numRows = parsed->size();
          for (char c : parsed->at(0))
          {

              if (c == ',')
              {
                  numComa++;
              }
          }
          numColumn = numComa + 1;

          representation = new State<T> *[numRows];
          cout <<"Building Matrix"<<endl;
          for (int i = 0; i < numRows; i++)
          { //going over y values
              representation[i] = new State<T>[numColumn];
              k = 0, l = 0; //used for iterating over the chars in a string representation of a specific matrix line
              for (int j = 0; j < numColumn; j++)
              { //going over x values
                  //cout << i << endl;
                  while (parsed->at(i)[k] != ',')
                  {
                      k++;
                  } //k on ','
                  cost = parsed->at(i).substr(l, k - l);

                  actualCost = stod(cost, &sz); // to cell

                  //cout << "x value: " << j << ", y value: " << i << " cost: " << actualCost << endl;

                  //representation[j + numRows * i] = new State<T>(j, i, actualCost);

                  State<T> toPut = State<T>(j, i, actualCost);

                  representation[i][j] = toPut;

                  k++;
                  l = k;
              }
          }

          setFieldsSearchable(startP, endP); //setting the fields defined in Searchable

          cout <<"Matrix was created"<<endl;
      }
  }

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
      ///// -1 ==>> ein sofffff!!!!!!!!!!!!!! TAKE INTO ACCOUNT
      int xOverCheck = overItCheck.getStateType().getX();
      int yOverCheck = overItCheck.getStateType().getY();
      vector<State<T>> vecSteps;
      // 8 ifim
      if (xOverCheck == 0 && yOverCheck == 0) // up left corner
      {
          State<T> goRight = representation[0][1];
          State<T> goDown = representation[1][0];
          if (goRight.getCost() != -1)
          {
              vecSteps.emplace_back(goRight);
          }
          if (goDown.getCost() != -1)
          {
              vecSteps.emplace_back(goDown);
          }
          return vecSteps;
      }
      if (xOverCheck == 0 && yOverCheck == numColumn - 1)
      { //up right corner

          State<T> goLeft = representation[0][numColumn - 2];
          State<T> goDown = representation[1][yOverCheck];
          if (goLeft.getCost() != -1)
          {
              vecSteps.emplace_back(goLeft);
          }
          if (goDown.getCost() != -1)
          {
              vecSteps.emplace_back(goDown);
          }
          return vecSteps;
      }
      if (xOverCheck == numRows - 1 && yOverCheck == 0)
      { // left dowm corner
          State<T> goUp = representation[numRows - 2][0];
          State<T> goRight = representation[xOverCheck][1];
          if (goUp.getCost() != -1)
          {
              vecSteps.emplace_back(goUp);
          }
          if (goRight.getCost() != -1)
          {
              vecSteps.emplace_back(goRight);
          }
          return vecSteps;
      }
      if (xOverCheck == numRows - 1 && yOverCheck == numColumn - 1)
      {
          State<T> goLeft = representation[xOverCheck][yOverCheck - 1];
          State<T> goUp = representation[xOverCheck - 1][yOverCheck];
          if (goLeft.getCost() != -1)
          {
              vecSteps.emplace_back(goLeft);
          }
          if (goUp.getCost() != -1)
          {
              vecSteps.emplace_back(goUp);
          }
          return vecSteps;
      }
      if (xOverCheck == 0)
      { // first row
          State<T> goLeft = representation[0][yOverCheck - 1];
          State<T> goRight = representation[0][yOverCheck + 1];
          State<T> goDown = representation[1][yOverCheck];
          if (goLeft.getCost() != -1)
          {
              vecSteps.emplace_back(goLeft);
          }
          if (goRight.getCost() != -1)
          {
              vecSteps.emplace_back(goRight);
          }
          if (goDown.getCost() != -1)
          {
              vecSteps.emplace_back(goDown);
          }
          return vecSteps;
      }
      if (yOverCheck == 0)
      { //  first column
          State<T> goUp = representation[xOverCheck - 1][0];
          State<T> goDown = representation[xOverCheck + 1][0];
          State<T> goRight = representation[xOverCheck][1];
          if (goUp.getCost() != -1)
          {
              vecSteps.emplace_back(goUp);
          }
          if (goDown.getCost() != -1)
          {
              vecSteps.emplace_back(goDown);
          }
          if (goRight.getCost() != -1)
          {
              vecSteps.emplace_back(goRight);
          }
          return vecSteps;
      }
      if (xOverCheck == numRows - 1)
      { // last row
          State<T> goLeft = representation[xOverCheck - 1][yOverCheck];
          State<T> goRight = representation[xOverCheck + 1][yOverCheck];
          State<T> goUp = representation[xOverCheck][yOverCheck];
          if (goLeft.getCost() != -1)
          {
              vecSteps.emplace_back(goLeft);
          }
          if (goRight.getCost() != -1)
          {
              vecSteps.emplace_back(goRight);
          }
          if (goUp.getCost() != -1)
          {
              vecSteps.emplace_back(goUp);
          }
          return vecSteps;
      }
      if (yOverCheck == numColumn - 1)
      { // last column
          State<T> goUp = representation[xOverCheck - 1][yOverCheck];
          State<T> goDown = representation[xOverCheck + 1][yOverCheck];
          State<T> goLeft = representation[xOverCheck][yOverCheck - 1];
          if (goUp.getCost() != -1)
          {
              vecSteps.emplace_back(goUp);
          }
          if (goDown.getCost() != -1)
          {
              vecSteps.emplace_back(goDown);
          }
          if (goLeft.getCost() != -1)
          {
              vecSteps.emplace_back(goLeft);
          }
          return vecSteps;
      }
      if ((0 < xOverCheck < numRows - 1) && (0 < yOverCheck < numColumn - 1)) // middle
      {
          State<T> goLeft = representation[xOverCheck][yOverCheck - 1];
          State<T> goRight = representation[xOverCheck][yOverCheck + 1];
          State<T> goUp = representation[xOverCheck - 1][yOverCheck];
          State<T> goDown = representation[xOverCheck + 1][yOverCheck];
          if (goLeft.getCost() != -1)
          {
              vecSteps.emplace_back(goLeft);
          }
          if (goRight.getCost() != -1)
          {
              vecSteps.emplace_back(goRight);
          }
          if (goUp.getCost() != -1)
          {
              vecSteps.emplace_back(goUp);
          }
          if (goDown.getCost() != -1)
          {
              vecSteps.emplace_back(goDown);
          }
          return vecSteps;
      }
      return vecSteps;
  }

  void setFieldsSearchable(const string &start, const string &end)
  {
      string intermediate, updatedStr, left, right;
      int xVal, yVal, j = 0;
      double costVal;

      //setting initial state
      stringstream check1(start);
      while (getline(check1, intermediate, ' '))
      {
          updatedStr += intermediate;
      }

      while (updatedStr[j] != ',')
      {
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
      updatedStr = "", left = "", right = "", intermediate = "";

      stringstream check2(end);
      while (getline(check2, intermediate, ' '))
      {
          updatedStr += intermediate;
      }

      j = 0;
      while (updatedStr[j] != ',')
      {
          left += updatedStr[j]; //creating the x value of the point
          j++;
      } //j on ','

      right = updatedStr.substr(j + 1, updatedStr.length() - (j + 1)); //y value of the point

      //converting the x and y values (represented with strings) to ints
      stringstream leftNumEnd(left);
      leftNumEnd >> xVal;
      stringstream rightNumEnd(right);
      rightNumEnd >> yVal;

      State<T> stateGoal(xVal, yVal, representation[xVal][yVal].getCost());
      setDestPos(stateGoal);
  }

  void setCurPos(State<T> current)
  {
      this->curPos = current;
  }

  void setInitPos(State<T> initial)
  {
      this->initPos = initial;
  }

  void setDestPos(State<T> dest)
  {
      this->destPos = dest;
  }
};
#endif