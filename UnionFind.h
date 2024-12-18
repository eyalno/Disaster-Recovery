#pragma once

#include <unordered_map>

class UnionFind {
private:
    std::unordered_map<int, int> root;
    std::unordered_map<int, int> rank;

public:
    bool addCommit(int x);
    int find(int x);
    bool unionSets(int x, int y);
};


