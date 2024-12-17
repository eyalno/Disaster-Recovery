#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <unordered_map>

class UnionFind {
private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;

public:
    bool addCommit(int x);
    int find(int x);
    bool unionSets(int x, int y);
};

#endif // UNIONFIND_H
