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

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator==(
          const T &value) const
        {
            return m_value == static_cast<IntType>(value);
        }

        bool operator==(const IntValue &value) const { return m_value == value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator!=(
          const T &value) const
        {
            return m_value != static_cast<IntType>(value);
        }

        bool operator!=(const IntValue &value) const { return m_value != value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<=(
          const T &value) const
        {
            return m_value <= static_cast<IntType>(value);
        }

        bool operator<=(const IntValue &value) const { return m_value <= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<(
          const T &value) const
        {
            return m_value < static_cast<IntType>(value);
        }

        bool operator<(const IntValue &value) const { return m_value < value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>=(
          const T &value) const
        {
            return m_value >= static_cast<IntType>(value);
        }

        bool operator>=(const IntValue &value) const { return m_value >= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>(
          const T &value) const
        {
            return m_value > static_cast<IntType>(value);
        }

        bool operator>(const IntValue &value) const { return m_value > value.m_value; }

        IntValue operator-() const { return IntValue(-m_value); }

        IntValue operator~() const { return IntValue(~m_value); }

        IntValue operator+() const { return IntValue(m_value); }

        IntValue &operator++()
        {
            ++m_value;
            return *this;
        }

        IntValue operator++(int) { return IntValue(m_value++); }

        IntValue &operator--()
        {
            --m_value;
            return *this;
        }

        IntValue operator--(int) { return IntValue(m_value--); }

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
          const T &value) const
        {
            return IntValue(m_value + static_cast<IntType>(value));
        }

        IntValue operator+(const IntValue &value) const
        {
            return IntValue(m_value + value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator-(
          const T &value) const
        {
            return IntValue(m_value - static_cast<IntType>(value));
        }

        IntValue operator-(const IntValue &value) const
        {
            return IntValue(m_value - value.m_value);
        }

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
          const T &value) const
        {
            return IntValue(m_value * static_cast<IntType>(value));
        }

        IntValue operator*(const IntValue &value) const
        {
            return IntValue(m_value * value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator/(
          const T &value) const
        {
            return IntValue(m_value / static_cast<IntType>(value));
        }

        IntValue operator/(const IntValue &value) const
        {
            return IntValue(m_value / value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator%=(
          const T &value)
        {
            m_value %= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator%=(const IntValue &value)
        {
            m_value %= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator%(
          const T &value) const
        {
            return IntValue(m_value % static_cast<IntType>(value));
        }

        IntValue operator%(const IntValue &value) const
        {
            return IntValue(m_value % value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator<<=(
          const T &value)
        {
            m_value <<= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator<<=(const IntValue &value)
        {
            m_value <<= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator>>=(
          const T &value)
        {
            m_value >>= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator>>=(const IntValue &value)
        {
            m_value >>= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator<<(
          const T &value) const
        {
            return IntValue(m_value << static_cast<IntType>(value));
        }

        IntValue operator<<(const IntValue &value) const
        {
            return IntValue(m_value << value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator>>(
          const T &value) const
        {
            return IntValue(m_value >> static_cast<IntType>(value));
        }

        IntValue operator>>(const IntValue &value) const
        {
            return IntValue(m_value >> value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator&=(
          const T &value)
        {
            m_value &= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator&=(const IntValue &value)
        {
            m_value &= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator&(
          const T &value) const
        {
            return IntValue(m_value & static_cast<IntType>(value));
        }

        IntValue operator&(const IntValue &value) const
        {
            return IntValue(m_value & value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator|=(
          const T &value)
        {
            m_value |= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator|=(const IntValue &value)
        {
            m_value |= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator|(
          const T &value) const
        {
            return IntValue(m_value | static_cast<IntType>(value));
        }

        IntValue operator|(const IntValue &value) const
        {
            return IntValue(m_value | value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator^=(
          const T &value)
        {
            m_value ^= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator^=(const IntValue &value)
        {
            m_value ^= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator^(
          const T &value) const
        {
            return IntValue(m_value ^ static_cast<IntType>(value));
        }

        IntValue operator^(const IntValue &value) const
        {
            return IntValue(m_value ^ value.m_value);
        }
    };
} // namespace FDCore

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator==(
  const T &value, const FDCore::IntValue &other)
{
    return other == value;
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator!=(
  const T &value, const FDCore::IntValue &other)
{
    return other != value;
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<=(
  const T &value, const FDCore::IntValue &other)
{
    return value <= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<(
  const T &value, const FDCore::IntValue &other)
{
    return value < static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>=(
  const T &value, const FDCore::IntValue &other)
{
    return value >= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>(
  const T &value, const FDCore::IntValue &other)
{
    return value > static_cast<T>(other);
}

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

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> operator<<=(const T &value,
                                                       const FDCore::IntValue &other)
{
    return value <<= static_cast<const FDCore::IntValue::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> operator<<(const T &value, const FDCore::IntValue &other)
{
    return value << static_cast<const FDCore::IntValue::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> &operator>>=(const T &value, FDCore::IntValue &other)
{

    return value >>= static_cast<const FDCore::IntValue::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> &operator>>(const T &value, FDCore::IntValue &other)
{

    return value >> static_cast<const FDCore::IntValue::IntType &>(other);
}

template<typename StreamType>
std::enable_if_t<!std::is_integral_v<StreamType>, StreamType> &operator<<(
  StreamType &stream, const FDCore::IntValue &value)
{
    stream << static_cast<const FDCore::IntValue::IntType &>(value);
    return stream;
}

template<typename StreamType>
std::enable_if_t<!std::is_integral_v<StreamType>, StreamType> &operator>>(StreamType &stream,
                                                                          FDCore::IntValue &value)
{
    FDCore::IntValue::IntType tmp;
    stream >> tmp;
    value = tmp;
    return stream;
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator&=(
  T &value, FDCore::IntValue &other)
{
    return value &= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator&(
  const T &value, FDCore::IntValue &other)
{
    return value & static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator|=(
  T &value, FDCore::IntValue &other)
{
    return value |= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator|(
  const T &value, FDCore::IntValue &other)
{
    return value | static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator^=(
  T &value, FDCore::IntValue &other)
{
    return value ^= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator^(
  const T &value, FDCore::IntValue &other)
{
    return value ^ static_cast<T>(other);
}

#endif // FDCORE_INTVALUE_H
