#pragma once

#include "File.h"
#include <vector>
#include <cstdint>

struct Commit {
    uint64_t id{};
    uint64_t timeStamp{};
    std::vector<File> files;
};

