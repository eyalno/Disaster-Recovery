#include "UnionFind.h"

bool UnionFind::addCommit(int x) {
    auto [_, success] = root.insert({x, x});
    if (success) {
        rank[x] = 1;
    }
    return success;
}

// path compression optimization 
int UnionFind::find(int x) {
    if (root.find(x) == root.end()) {
        root[x] = x;
    }
    if (root[x] != x) {
        root[x] = find(root[x]);  
    }
    return root[x];
}

//union by rank optimization
bool UnionFind::unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return false;

    if (rank[rootX] > rank[rootY]) {
        root[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
        root[rootX] = rootY;
    } else {
        root[rootY] = rootX;
        rank[rootX]++;
    }
    return true;
}
