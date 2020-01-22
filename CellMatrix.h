#ifndef _CellMatrix_h_
#define _CellMatrix_h_
using namespace std;

class CellMatrix
{
private:
    int x, y;
    double costCell; // ? delete or not. This is a QUESTION
public:
    CellMatrix(){
        
    }
    CellMatrix(int xParsed, int yParsed, double costOutSide)
    {
        this->x = xParsed;
        this->y = yParsed;
        this->costCell = costOutSide;
    }
    int getX()
    {
        return this->x;
    }
    int getY()
    {
        return this->y;
    }
    double getCellCost()
    {
        return this->costCell;
    }
    bool equalCheck(CellMatrix cell)
    {
        if ((x == cell.getX()) && (y == cell.getY()))
        {
            return true;
        }
        return false;
    }
    string toString(){
        string s = "(" +to_string(x) + ",";
        s += to_string(y) + ")";
        return s;
    }
};


#endif