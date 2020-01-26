cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)


add_executable(ex4 testC.cpp MyTestClientHandler.cpp String.h
        StringReverser.h MyTestClientHandler.h MyClientSearchClientHandler.cpp
        CacheManager.h CellMatrix.h ClientHandler.h FileCacheManager.h
        Matrix.h MyClientSearchClientHandler.h MySerialServer.h Searchable.h Searcher.h
        SearcherAdapter.h Server.h Solver.h State.h AStar.h
        StringReverseAdapter.h compareStates.h BestFirstSearch.h MyPriorityQueue.h
        ISearcher.h ParallelServer.h BFS.h DFS.h)


