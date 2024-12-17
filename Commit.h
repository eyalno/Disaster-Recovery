#ifndef COMMIT_H
#define COMMIT_H

#include "File.h"
#include <vector>
#include <cstdint>

struct Commit {
    uint64_t id = 0;
    uint64_t timeStamp = 0;
    std::vector<File> files;
};

#endif // COMMIT_H