#ifndef FDCORE_COMMON_SPAN_H
#define FDCORE_COMMON_SPAN_H

#include <cstdint>

namespace FDCore
{
    template<typename T, typename SizeType = uint32_t>
    struct Span
    {
        typedef SizeType size_type;
        typedef T value_type;

        size_type size;
        value_type *data;
    };
} // namespace FDCore

#endif // FDCORE_COMMON_SPAN_H