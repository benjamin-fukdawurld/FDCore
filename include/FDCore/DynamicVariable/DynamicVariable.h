#ifndef FDCORE_DYNAMICVARIABLE_H
#define FDCORE_DYNAMICVARIABLE_H

#include <FDCore/DynamicVariable/AbstractValue.h>
#include <FDCore/DynamicVariable/BoolValue.h>
#include <FDCore/DynamicVariable/FloatValue.h>
#include <FDCore/DynamicVariable/IntValue.h>
#include <FDCore/DynamicVariable/StringValue.h>
#include <memory>

namespace FDCore
{
    class DynamicVariable
    {
      private:
        std::shared_ptr<AbstractValue> m_value;

        DynamicVariable();
        DynamicVariable(ValueType type);
        DynamicVariable(const DynamicVariable &) = default;
        DynamicVariable(DynamicVariable &&) = default;

        virtual ~DynamicVariable() = default;

        DynamicVariable &operator=(const DynamicVariable &) = default;
        DynamicVariable &operator=(DynamicVariable &&) = default;

        DynamicVariable &operator=(StringValue::StringType &&str);
        DynamicVariable &operator=(const StringValue::StringType &str);

        DynamicVariable &operator=(bool value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator=(const T &value)
        {
            m_value = std::make_shared<FDCore::IntValue>(value);
            return *this;
        }

        template<typename T>
        std::enable_if_t<std::is_floating_point_v<T>, DynamicVariable> &operator=(const T &value)
        {
            m_value = std::make_shared<FDCore::FloatValue>(value);
            return *this;
        }

        ValueType getValueType() const
        {
            return !m_value ? ValueType::None : m_value->getValueType();
        }

        bool isType(ValueType type) const { return type == getValueType(); }
    };

} // namespace FDCore

#endif // FDCORE_DYNAMICVARIABLE_H
