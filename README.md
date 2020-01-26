# Ex4_Server_That_Solves_Problems
EX4 is a C++ project, used to receive problems from several clients simuteneoulsy and returns solution to each one of them.
Based on empirical experiments we have found out that algo A* is preferable over others to search for optimal solution.


## Installation

Download the zip file of the project from the following [link]() in the github website(The branch called "master"), by pressing on the green button "clone or download".

All the files needed to run the program are in this folder.


## Running the project

First, unzip the file.

Now we can compile the project files with the following command in the commandline(terminal):

```bash
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o SERVER -pthread
```

Now, that an execution file a.out naming "SERVER" is created, we can run the program, while also passing the name of the txt file containing the code we interpret. For example:

```bash
SERVER [PORT]
```

After running the program, we also run a lot of clients that are interested in solving their matrix problems of finding minimum distance to destination.

## Comments

1. Our program runs perfectly with  python script "auto_client.py" with any port except to 5600.By the way a lot of students met this problem, so there is a sitution that you should also run with some other port.
2. The current folder you have downloaded also includes the following files:
   A pdf file that deals with the empirical experiments we made, 10 files where each contains a different matrix as an            input problem, and 4 files - each containing the results of the experiments we have done.
