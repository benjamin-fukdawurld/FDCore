#ifndef FDCORE_VALUETYPE_H
#define FDCORE_VALUETYPE_H

#include <cstdint>
#include <string>

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

namespace std
{
    inline string to_string(FDCore::ValueType type)
    {
        switch(type)
        {
            case FDCore::ValueType::None:
                return "None";

            case FDCore::ValueType::Boolean:
                return "Boolean";

            case FDCore::ValueType::Integer:
                return "Integer";

            case FDCore::ValueType::Float:
                return "Float";

            case FDCore::ValueType::String:
                return "String";

            case FDCore::ValueType::Function:
                return "Function";

            case FDCore::ValueType::Array:
                return "Array";

            case FDCore::ValueType::Object:
                return "Object";
        }
    }
} // namespace std

#endif // FDCORE_VALUETYPE_H