#ifndef FDCORE_DYNAMICVARIABLE_H
#define FDCORE_DYNAMICVARIABLE_H

#include <FDCore/DynamicVariable/AbstractValue.h>
#include <memory>

namespace FDCore
{
    class DynamicVariable
    {
      private:
        std::shared_ptr<AbstractValue> m_value;

        DynamicVariable();
        DynamicVariable(ValueType type);

        ValueType getValueType() const
        {
            return !m_value ? ValueType::None : m_value->getValueType();
        }

        bool isType(ValueType type) const { return type == getValueType(); }
    };

} // namespace FDCore

#endif // FDCORE_DYNAMICVARIABLE_H
