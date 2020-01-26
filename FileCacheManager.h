#ifndef _FileCacheManager_h_
#define _FileCacheManager_h_
#include "CacheManager.h"
#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include "FileCacheManager.h"
#include <fstream>

using namespace std;

template <typename Problem, typename Solution>

class FileCacheManager : public CacheManager<Problem, Solution>
{

public:
    bool existSolution(Problem& problem) {
        string fileName = problem.toString();
        string updatedFileName = "Prob";
        hash<string> myHash;

        updatedFileName += to_string(myHash(fileName));

        fstream file(updatedFileName);

        if (file) {
            file.close();
            return true;

        } else {
            file.close();
            return false;
        }
    }

    bool existSolution(Problem* problem) {
        string fileName = problem->toString();
        string updatedFileName = "Prob";
        hash<string> myHash;

        updatedFileName += to_string(myHash(fileName));

        fstream file(updatedFileName);

        if (file) {
            file.close();
            return true;

        } else {
            file.close();
            return false;
        }
    }

    void addSolutionToBase(Solution &solution, Problem &problem) {
        string fileName = problem.toString();
        string updatedFileName = "Prob";
        hash<string> myHash;

        updatedFileName += to_string(myHash(fileName));

        //writing solution to a specific file
        ofstream file(updatedFileName);

        file << solution << endl;
        file.close();
    }

    void addSolutionToBase(Solution& solution, Problem* problem) {
        string fileName = problem->toString();
        string updatedFileName = "Prob";
        hash<string> myHash;

        updatedFileName += to_string(myHash(fileName));

        //writing solution to a specific file
        ofstream file(updatedFileName);

        file << solution << endl;
        file.close();

    }

    Solution getSolution(Problem &problem) {
        string fileName = problem.toString();
        string updatedFileName = "Prob";
        string line;
        hash<string> myHash;

        updatedFileName += to_string(myHash(fileName));
        fstream file;
        Solution solution;

        file.open(updatedFileName, ios::in | ios::binary);
        if (file.is_open())
        {
            while (getline(file, line)) {
                solution += line;
            }

            file.close();
        }
        else
        {
            throw "error - cannot load file";
        }

        return solution;
    }

    Solution getSolution(Problem* problem) {
        string fileName = problem->toString();
        string updatedFileName = "Prob";
        string line;
        hash<string> myHash;

        updatedFileName += to_string(myHash(fileName));
        fstream file;
        Solution solution;

        file.open(updatedFileName, ios::in | ios::binary);
        if (file.is_open())
        {
            while (getline(file, line)) {
                solution += line;
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
