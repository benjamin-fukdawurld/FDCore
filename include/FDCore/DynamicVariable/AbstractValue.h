#ifndef FDCORE_ABSTRACTVALUE_H
#define FDCORE_ABSTRACTVALUE_H

#include <FDCore/DynamicVariable/ValueType.h>

namespace FDCore
{
    class AbstractValue
    {
      public:
        AbstractValue() = default;
        AbstractValue(AbstractValue &&) = default;
        AbstractValue(const AbstractValue &) = default;

        virtual ~AbstractValue() noexcept = default;

        AbstractValue &operator=(AbstractValue &&) = default;
        AbstractValue &operator=(const AbstractValue &) = default;

        virtual ValueType getValueType() const = 0;
        virtual bool isType(ValueType type) const { return type == getValueType(); }
    };
} // namespace FDCore

#endif // FDCORE_ABSTRACTVALUE_H
