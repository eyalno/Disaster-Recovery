#include "File.h"

File::File(const std::string& path, const std::string& opaqueID)
    : path(path), opaqueID(opaqueID) {}

const std::string& File::getPath() const {
    return path;
}

const std::string& File::getOpaqueID() const {
    return opaqueID;
} 