#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <memory>
#include <string>

namespace FDCore
{
    std::unique_ptr<char[]> readFile(const std::string &fileName);
    std::unique_ptr<uint8_t[]> readBinaryFile(const std::string &fileName, size_t &size);
}

#endif // FILEUTILS_H
