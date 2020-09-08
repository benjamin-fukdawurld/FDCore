#ifndef FDCORE_ABSTRACTVALUE_H
#define FDCORE_ABSTRACTVALUE_H

#include <FDCore/DynamicVariable/ValueType.h>

namespace FDCore
{
    class AbstractValue
    {
      public:
        AbstractValue() = default;
        virtual ~AbstractValue() = default;

        virtual ValueType getValueType() const = 0;
        virtual bool isType(ValueType type) const { return type == getValueType(); }
    };
} // namespace FDCore

#endif // FDCORE_ABSTRACTVALUE_H