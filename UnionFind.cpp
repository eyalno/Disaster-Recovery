#include "UnionFind.h"

bool UnionFind::addCommit(int x) {
    auto [_, success] = parent.insert({x, x});
    if (success) {
        rank[x] = 1;
    }
    return success;
}

int UnionFind::find(int x) {
    if (parent.find(x) == parent.end()) {
        parent[x] = x;
    }
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

bool UnionFind::unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return false;

    if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    return true;
}
