#ifndef FILE_H
#define FILE_H

#include <string>

class File {
private:
    std::string path;
    std::string opaqueID;

public:
    File(const std::string& path, const std::string& opaqueID);
    const std::string& getPath() const;
    const std::string& getOpaqueID() const;
};

#endif // FILE_H