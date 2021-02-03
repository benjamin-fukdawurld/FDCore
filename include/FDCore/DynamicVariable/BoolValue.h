#ifndef FDCORE_DYNAMICVARIABLE_BOOLVALUE_H
#define FDCORE_DYNAMICVARIABLE_BOOLVALUE_H

#include <FDCore/DynamicVariable/AbstractValue.h>

namespace FDCore
{
    class BoolValue : public AbstractValue
    {
      private:
        bool m_value;

      public:
        BoolValue() : BoolValue(false) {}
        explicit BoolValue(bool value) : m_value(value) {}

        BoolValue(BoolValue &&) = default;
        BoolValue(const BoolValue &) = default;
        ~BoolValue() override = default;

        ValueType getValueType() const override { return ValueType::Boolean; }

        BoolValue &operator=(bool value)
        {
            m_value = value;
            return *this;
        }

        BoolValue &operator=(BoolValue &&) = default;
        BoolValue &operator=(const BoolValue &) = default;

        explicit operator bool() const { return m_value; }

        bool operator!() const { return !m_value; }

        bool operator&&(bool other) const { return m_value && other; }
        bool operator&&(const BoolValue &other) const { return m_value && other.m_value; }

        bool operator||(bool other) const { return m_value || other; }
        bool operator||(const BoolValue &other) const { return m_value || other.m_value; }
    };
} // namespace FDCore

bool operator&&(bool a, const FDCore::BoolValue &b) { return b && a; }

bool operator||(bool a, const FDCore::BoolValue &b) { return b || a; }

template<typename StreamType>
StreamType &operator<<(StreamType &stream, const FDCore::BoolValue &value)
{
    return stream << static_cast<bool>(value);
}

template<typename StreamType>
StreamType &operator>>(StreamType &stream, FDCore::BoolValue &value)
{
    bool tmp = 0;
    stream >> tmp;
    value = tmp;
    return stream;
}

#endif // FDCORE_DYNAMICVARIABLE_BOOLVALUE_H
