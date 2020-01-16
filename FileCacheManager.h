#ifndef _FileCacheManager_h_
#define _FileCacheManager_h_
#include "CacheManager.h"
#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include "String.h"
#include "FileCacheManager.h"
#include <fstream>

using namespace std;

template <typename Problem, typename Solution>

class FileCacheManager : public CacheManager<Problem, Solution>
{
private:
    unordered_map<string, string> fileSolution;

public:
    bool existSolution(Problem& problem)
    {

        if (this->fileSolution.find(problem.toString()) == this->fileSolution.end())
        {
            return false;
        }
        return true;
    }
    void addSolutionToBase(Solution &solution, Problem &problem)
    {

        hash<string> hashingOnProblem;
        string fileName = "Problem" + hashingOnProblem(problem.toString());
        this->fileSolution.insert({problem.toString(), fileName});

        //writing solution to a specific file
        fstream file;
        file.open(fileName, ios::out | ios::binary);
        if (file.is_open())
        {
            if (!file.write((char *)&solution, sizeof(solution)))
            {
                throw "Error - couldn't write into the file";
            }
            file.close();
        }
        else
        {
            throw "Error- couldn't open file";
        }
    }

    Solution getSolution(Problem &problem)
    {
        string fileName = this->fileSolution[problem.toString()];
        fstream file;
        Solution solution;

        file.open(fileName, ios::in | ios::binary);
        if (file.is_open())
        {

            if (!file.read((char *)&solution, sizeof(solution)))
            {
                throw "Error - couldn't read from file";
            }
            file.close();
        }
        else
        {
            throw "error - cannot load file";
        }

        return solution;
    }
};
#endif
