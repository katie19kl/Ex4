#include "MyTestClientHandler.h"
#include <string>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>

char* extractStr(char[]);

void MyTestClientHandler::handleClient(int client_socket)
{
    try
    {
      char buffer[2048];
      read(client_socket, buffer, 2048);

      char *actText = extractStr(buffer);

      string problem(actText);
      string solution;

      String strProblem;

      strProblem.setString(problem);

      if (this->cache->existSolution(strProblem))
      {
        solution = this->cache->getSolution(strProblem);
      }
      else
      {
        solution = this->solver->solve(strProblem);
        this->cache->addSolutionToBase(solution, strProblem);
      }

      char solutionArr[solution.length() + 1];
      strcpy(solutionArr, solution.c_str());
      send(client_socket, solutionArr, strlen(solutionArr), 0);
      
      delete actText;

    }

    catch (exception &e)
    {
      if (client_socket != -1)
      {
        close(client_socket);
        exit(1);
      }
    }
}

char *extractStr(char buffer[])
{
  int i = 0, j = 0;

  while (buffer[i] != '\n')
  {
    i++;
  }
  char *actText = new char(i);
  while (j != i)
  {
    actText[j] = buffer[j];
    j++;
  }
  return actText;
}
