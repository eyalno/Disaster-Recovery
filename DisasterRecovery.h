#pragma once

#include "UnionFind.h"
#include "Commit.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>

class DisasterRecovery {
private:
    size_t N{};
    std::vector<Commit> commits;
    
    //a 2 level map container of file name -> opauqeId -> commit ID.
    //opauqeId -> file name -> commit ID.
    //i couldn't figure ot a more efficent container to check for ambiguity 
    //one cointainer to store all files uniqely.
    std::unordered_map<std::string, std::unordered_map<std::string, int>> pathIdCommit;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> idPathCommit;
    UnionFind unionFind;
    std::unordered_map<int, std::vector<Commit>> repositories;

    void processCommit(const std::string& inputLine);
    void buildRepositories();
    void handleQueries(int R,std::ifstream & inputFile);


    static constexpr const char* ambigiousMSG = "AMBIGUOUS INPUT!";
    static constexpr const char* testPath = "Test Input/input.txt";
    static constexpr const char* fileNotOpenMSG = "Error: Could not open input.txt";



public:
    void run();
};

