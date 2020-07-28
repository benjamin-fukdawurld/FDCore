#ifndef FDCORE_FILEUTILS_H
#define FDCORE_FILEUTILS_H

#include <FDCore/Common/Macros.h>
#include <memory>
#include <string>

namespace FDCore
{
    FD_EXPORT std::unique_ptr<char[]> readFile(const std::string &fileName);
    FD_EXPORT std::unique_ptr<uint8_t[]> readBinaryFile(const std::string &fileName, size_t &size);
} // namespace FDCore

#endif // FDCORE_FILEUTILS_H
