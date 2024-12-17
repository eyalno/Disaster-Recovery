#ifndef DISASTERRECOVERY_H
#define DISASTERRECOVERY_H

#include "UnionFind.h"
#include "Commit.h"
#include <unordered_map>
#include <vector>
#include <string>

class DisasterRecovery {
private:
    size_t N;
    std::vector<Commit> commits;
    //a 2 level map container of file name -> opauqeId -> commit ID.
    std::unordered_map<FILE, int>> fileToRepo;
    UnionFind unionFind;
    std::unordered_map<int, std::vector<Commit>> repositories;

    void processCommit(const std::string& inputLine);
    void buildRepositories();
    void handleQueries(int R);

public:
    void run();
};

#endif // DISASTERRECOVERY_H