#ifndef FDCORE_INTVALUE_H
#define FDCORE_INTVALUE_H

#ifndef FDCORE_INT_TYPE
    #define FDCORE_INT_TYPE int64_t
#endif // FDCORE_INT_TYPE

#include <FDCore/DynamicVariable/AbstractValue.h>

namespace FDCore
{
    class IntValue : public AbstractValue
    {
      public:
        typedef FDCORE_INT_TYPE IntType;

      private:
        IntType m_value;

      public:
        IntValue() : m_value(0) {}

        template<
          typename T,
          typename U = std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntType>>
        explicit IntValue(T value) : m_value(static_cast<IntType>(value))
        {
        }

        IntValue(IntValue &&) = default;
        IntValue(const IntValue &) = default;

        ~IntValue() noexcept override = default;

        ValueType getValueType() const override { return ValueType::Integer; }

        IntValue &operator=(IntValue &&) = default;
        IntValue &operator=(const IntValue &) = default;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator=(
          const T &value)
        {
            m_value = static_cast<IntType>(value);
            return *this;
        }

        template<
          typename T,
          typename U = std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T>>
        explicit operator T() const
        {
            return static_cast<T>(m_value);
        }

        IntValue operator-() { return IntValue(-m_value); }

        IntValue operator+() { return IntValue(m_value); }

        IntValue &operator++()
        {
            ++m_value;
            return *this;
        }

        IntValue &operator++(int)
        {
            m_value++;
            return *this;
        }

        IntValue &operator--()
        {
            --m_value;
            return *this;
        }

        IntValue &operator--(int)
        {
            m_value--;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator+=(
          const T &value)
        {
            m_value += static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator+=(const IntValue &value)
        {
            m_value += value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator-=(
          const T &value)
        {
            m_value -= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator-=(const IntValue &value)
        {
            m_value -= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator+(
          const T &value)
        {
            return IntValue(m_value + static_cast<IntType>(value));
        }

        IntValue operator+(const IntValue &value) { return IntValue(m_value + value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator-(
          const T &value)
        {
            return IntValue(m_value - static_cast<IntType>(value));
        }

        IntValue operator-(const IntValue &value) { return IntValue(m_value - value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator*=(
          const T &value)
        {
            m_value *= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator*=(const IntValue &value)
        {
            m_value *= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator/=(
          const T &value)
        {
            m_value /= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator/=(const IntValue &value)
        {
            m_value /= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator*(
          const T &value)
        {
            return IntValue(m_value * static_cast<IntType>(value));
        }

        IntValue operator*(const IntValue &value) { return IntValue(m_value * value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator/(
          const T &value)
        {
            return IntValue(m_value / static_cast<IntType>(value));
        }

        IntValue operator/(const IntValue &value) { return IntValue(m_value / value.m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator%=(
          const T &value)
        {
            return m_value %= static_cast<IntType>(value);
        }

        IntValue &operator%=(const IntValue &value)
        {
            m_value %= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator%(
          const T &value)
        {
            return IntValue(m_value % static_cast<IntType>(value));
        }

        IntValue operator%(const IntValue &value) { return IntValue(m_value % value.m_value); }
    };
} // namespace FDCore

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator+=(
  T &value, const FDCore::IntValue &other)
{
    return value += static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator-=(
  T &value, const FDCore::IntValue &other)
{
    return value -= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator+(
  const T &value, const FDCore::IntValue &other)
{
    return value + static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator-(
  const T &value, const FDCore::IntValue &other)
{
    return value - static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator*=(
  T &value, const FDCore::IntValue &other)
{
    return value *= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator/=(
  T &value, const FDCore::IntValue &other)
{
    return value /= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator*(
  const T &value, const FDCore::IntValue &other)
{
    return value * static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator/(
  const T &value, const FDCore::IntValue &other)
{
    return value / static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator%=(
  T &value, const FDCore::IntValue &other)
{
    return value %= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator%(
  const T &value, const FDCore::IntValue &other)
{
    return value % static_cast<T>(other);
}

template<typename StreamType>
StreamType &operator<<(StreamType &stream, const FDCore::IntValue &value)
{
    return stream << static_cast<const FDCore::IntValue::IntType &>(value);
}

template<typename StreamType>
StreamType &operator>>(StreamType &stream, FDCore::IntValue &value)
{
    FDCore::IntValue::IntType tmp;
    stream >> tmp;
    value = tmp;
    return stream;
}

#endif // FDCORE_INTVALUE_H
