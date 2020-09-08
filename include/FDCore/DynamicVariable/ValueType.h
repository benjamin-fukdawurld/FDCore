#ifndef FDCORE_VALUETYPE_H
#define FDCORE_VALUETYPE_H

#include <cstdint>

namespace FDCore
{
    enum class ValueType : uint8_t
    {
        None,
        Boolean,
        Integer,
        Float,
        String,
        Function,
        Array,
        Object
    };
} // namespace FDCore

#endif // FDCORE_VALUETYPE_H