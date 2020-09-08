#ifndef FDCORE_PRIMITIVEVALUE_H
#define FDCORE_PRIMITIVEVALUE_H

#include <FDCore/DynamicVariable/AbstractValue.h>

namespace FDCore
{
    class IntValue : public AbstractValue
    {
      private:
        int64_t m_value;

      public:
        IntValue() : m_value(0) {}

        ValueType getValueType() const override { return ValueType::Integer; }

        template<typename T>
        explicit IntValue(T value)
        {
            operator=<T>(value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator=(
          const T &value)
        {
            m_value = static_cast<int64_t>(value);
        }

        template<
          typename T,
          typename U = std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T>>
        explicit operator T() const
        {
            return static_cast<T>(m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator++()
        {
            ++m_value;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator++(
          int)
        {
            m_value++;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator--()
        {
            --m_value;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator--(
          int)
        {
            m_value--;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator+=(
          const T &value)
        {
            m_value += static_cast<int64_t>(value);
        }

        IntValue &operator+=(const IntValue &value) { m_value += value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator-=(
          const T &value)
        {
            m_value -= static_cast<int64_t>(value);
        }

        IntValue &operator-=(const IntValue &value) { m_value -= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator+(
          const T &value)
        {
            return IntValue(m_value + static_cast<int64_t>(value));
        }

        IntValue operator+(const IntValue &value) { IntValue(m_value + value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator-(
          const T &value)
        {
            return IntValue(m_value - static_cast<int64_t>(value));
        }

        IntValue operator-(const IntValue &value) { IntValue(m_value - value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator*=(
          const T &value)
        {
            m_value *= static_cast<int64_t>(value);
        }

        IntValue &operator*=(const IntValue &value) { m_value *= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator/=(
          const T &value)
        {
            m_value /= static_cast<int64_t>(value);
        }

        IntValue &operator/=(const IntValue &value) { m_value /= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator*(
          const T &value)
        {
            return IntValue(m_value * static_cast<int64_t>(value));
        }

        IntValue operator*(const IntValue &value) { IntValue(m_value * value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator/(
          const T &value)
        {
            return IntValue(m_value / static_cast<int64_t>(value));
        }

        IntValue operator/(const IntValue &value) { IntValue(m_value / value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator%=(
          const T &value)
        {
            m_value %= static_cast<int64_t>(value);
        }

        IntValue &operator%=(const IntValue &value) { m_value %= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator%(
          const T &value)
        {
            return IntValue(m_value % static_cast<int64_t>(value));
        }

        IntValue operator%(const IntValue &value) { IntValue(m_value % value.m_value); }
    };

    class FloatValue : public AbstractValue
    {
      private:
        double m_value;

      public:
        FloatValue() : m_value(0) {}

        ValueType getValueType() const override { return ValueType::Float; }

        template<typename T>
        explicit FloatValue(T value)
        {
            operator=<T>(value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> &operator=(
          const T &value)
        {
            m_value = static_cast<int64_t>(value);
        }

        template<
          typename T,
          typename U = std::enable_if<!std::is_same_v<T, bool> && std::is_integral_v<T>, T>::type>
        explicit operator T() const
        {
            return static_cast<T>(m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue>
          &operator++()
        {
            ++m_value;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> &operator++(
          int)
        {
            m_value++;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue>
          &operator--()
        {
            --m_value;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> &operator--(
          int)
        {
            m_value--;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> &operator+=(
          const T &value)
        {
            m_value += static_cast<int64_t>(value);
        }

        FloatValue &operator+=(const FloatValue &value) { m_value += value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> &operator-=(
          const T &value)
        {
            m_value -= static_cast<int64_t>(value);
        }

        FloatValue &operator-=(const FloatValue &value) { m_value -= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> operator+(
          const T &value)
        {
            return FloatValue(m_value + static_cast<int64_t>(value));
        }

        FloatValue operator+(const FloatValue &value) { FloatValue(m_value + value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> operator-(
          const T &value)
        {
            return FloatValue(m_value - static_cast<int64_t>(value));
        }

        FloatValue operator-(const FloatValue &value) { FloatValue(m_value - value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> &operator*=(
          const T &value)
        {
            m_value *= static_cast<int64_t>(value);
        }

        FloatValue &operator*=(const FloatValue &value) { m_value *= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> &operator/=(
          const T &value)
        {
            m_value /= static_cast<int64_t>(value);
        }

        FloatValue &operator/=(const FloatValue &value) { m_value /= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> operator*(
          const T &value)
        {
            return FloatValue(m_value * static_cast<int64_t>(value));
        }

        FloatValue operator*(const FloatValue &value) { FloatValue(m_value * value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> operator/(
          const T &value)
        {
            return FloatValue(m_value / static_cast<int64_t>(value));
        }

        FloatValue operator/(const FloatValue &value) { FloatValue(m_value / value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> &operator%=(
          const T &value)
        {
            m_value %= static_cast<int64_t>(value);
        }

        FloatValue &operator%=(const FloatValue &value) { m_value %= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, FloatValue> operator%(
          const T &value)
        {
            return FloatValue(m_value % static_cast<int64_t>(value));
        }

        FloatValue operator%(const FloatValue &value) { FloatValue(m_value % value.m_value); }
    };
} // namespace FDCore

#endif // FDCORE_PRIMITIVEVALUE_H