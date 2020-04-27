#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <memory>
#include <string>

#include <FDCore/Macros.h>

namespace FDCore
{
    FD_EXPORT std::unique_ptr<char[]> readFile(const std::string &fileName);
    FD_EXPORT std::unique_ptr<uint8_t[]> readBinaryFile(const std::string &fileName, size_t &size);
}

#endif // FILEUTILS_H
