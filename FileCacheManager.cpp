#include "FileCacheManager.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

template <typename Problem, typename Solution>

void FileCacheManager<Problem, Solution>::addSolutionToBase(const Solution &solution,
                                                            const Problem &problem) {

  hash<string> hashingOnProblem;
  string fileName = "Problem" + hashingOnProblem(problem.toString());
  this->fileSolution.insert({problem.toString(), fileName});

  //writing solution to a specific file
  fstream file;
  file.open(fileName, ios::out | ios::binary);
  if(file.is_open()) {
    if(!file.write((char *) & solution, sizeof(solution))) {
      throw "Error - couldn't write into the file";
    }
    file.close();
  } else {
    throw "Error- couldn't open file";
  }
}

template <typename Problem, typename Solution>
bool FileCacheManager<Problem, Solution>::existSolution(const Problem &problem) {

    if (this->fileSolution.find(problem.toString()) == this->fileSolution.end()) {
        return false;
    }
    return true;
}

template <typename Problem, typename Solution>

Solution FileCacheManager<Problem, Solution>::getSolution(Problem &problem) {
  string fileName = this->fileSolution[problem.toString()];
  fstream file;
  Solution solution;

  file.open(fileName, ios:: in | ios:: binary);
  if(file.is_open()) {

    if (!file.read((char *) &solution, sizeof(solution))) {
      throw "Error - couldn't read from file";
    }
    file.close();
  } else {
    throw "error - cannot load file";
  }

  return solution;
}