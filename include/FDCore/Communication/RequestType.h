#ifndef FDCORE_COMMUNICATION_REQUESTTYPE_H
#define FDCORE_COMMUNICATION_REQUESTTYPE_H

#include <cstdint>

namespace FDCore
{
    enum class RequestType : uint8_t
    {
        Create,
        Read,
        Update,
        Delete
    };
} // namespace FDCore

#endif // FDCORE_COMMUNICATION_REQUESTTYPE_H