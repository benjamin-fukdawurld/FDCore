#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <FDCore/Macros.h>
#include <memory>
#include <string>

namespace FDCore
{
    FD_EXPORT std::unique_ptr<char[]> readFile(const std::string &fileName);
    FD_EXPORT std::unique_ptr<uint8_t[]> readBinaryFile(const std::string &fileName, size_t &size);
} // namespace FDCore

#endif // FILEUTILS_H
