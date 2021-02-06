#ifndef FDCORE_FLOATVALUE_H
#define FDCORE_FLOATVALUE_H

#ifndef FDCORE_FLOAT_TYPE
    #define FDCORE_FLOAT_TYPE double
#endif // FDCORE_FLOAT_TYPE

#include <FDCore/DynamicVariable/AbstractValue.h>
#include <math.h>
#include <type_traits>

namespace FDCore
{
    class FloatValue : public AbstractValue
    {
      public:
        typedef FDCORE_FLOAT_TYPE FloatType;

      private:
        FloatType m_value;

      public:
        FloatValue() : m_value(0) {}

        template<typename T,
                 typename U =
                   std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatType>>
        explicit FloatValue(T value) : m_value(static_cast<FloatType>(value))
        {
        }

        FloatValue(FloatValue &&) = default;
        FloatValue(const FloatValue &) = default;

        ~FloatValue() noexcept override = default;

        ValueType getValueType() const override { return ValueType::Float; }

        FloatValue &operator=(FloatValue &&) = default;
        FloatValue &operator=(const FloatValue &) = default;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue>
          &operator=(const T &value)
        {
            m_value = static_cast<FloatType>(value);
            return *this;
        }

        template<typename T,
                 typename U = std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>,
                                               FloatValue>>
        explicit operator T() const
        {
            return static_cast<T>(m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator==(
          const T &value) const
        {
            return m_value == static_cast<FloatType>(value);
        }

        bool operator==(const FloatValue &value) const { return m_value == value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator!=(
          const T &value) const
        {
            return m_value != static_cast<FloatType>(value);
        }

        bool operator!=(const FloatValue &value) const { return m_value != value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator<=(
          const T &value) const
        {
            return m_value <= static_cast<FloatType>(value);
        }

        bool operator<=(const FloatValue &value) const { return m_value <= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator<(
          const T &value) const
        {
            return m_value < static_cast<FloatType>(value);
        }

        bool operator<(const FloatValue &value) const { return m_value < value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator>=(
          const T &value) const
        {
            return m_value >= static_cast<FloatType>(value);
        }

        bool operator>=(const FloatValue &value) const { return m_value >= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator>(
          const T &value) const
        {
            return m_value > static_cast<FloatType>(value);
        }

        bool operator>(const FloatValue &value) const { return m_value > value.m_value; }

        FloatValue operator-() const { return FloatValue(-m_value); }

        FloatValue operator+() const { return FloatValue(m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue>
          &operator+=(const T &value)
        {
            m_value += static_cast<FloatType>(value);
            return *this;
        }

        FloatValue &operator+=(const FloatValue &value)
        {
            m_value += value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue>
          &operator-=(const T &value)
        {
            m_value -= static_cast<FloatType>(value);
            return *this;
        }

        FloatValue &operator-=(const FloatValue &value)
        {
            m_value -= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue> operator+(
          const T &value)
        {
            return FloatValue(m_value + static_cast<FloatType>(value));
        }

        FloatValue operator+(const FloatValue &value) const
        {
            return FloatValue(m_value + value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue> operator-(
          const T &value)
        {
            return FloatValue(m_value - static_cast<FloatType>(value));
        }

        FloatValue operator-(const FloatValue &value) const
        {
            return FloatValue(m_value - value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue>
          &operator*=(const T &value)
        {
            m_value *= static_cast<FloatType>(value);
            return *this;
        }

        FloatValue &operator*=(const FloatValue &value)
        {
            m_value *= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue>
          &operator/=(const T &value)
        {
            m_value /= static_cast<FloatType>(value);
            return *this;
        }

        FloatValue &operator/=(const FloatValue &value)
        {
            m_value /= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue> operator*(
          const T &value)
        {
            return FloatValue(m_value * static_cast<FloatType>(value));
        }

        FloatValue operator*(const FloatValue &value) const
        {
            return FloatValue(m_value * value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue> operator/(
          const T &value)
        {
            return FloatValue(m_value / static_cast<FloatType>(value));
        }

        FloatValue operator/(const FloatValue &value) const
        {
            return FloatValue(m_value / value.m_value);
        }
    };
} // namespace FDCore

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator+=(
  T &value, const FDCore::FloatValue &other)
{
    return value += static_cast<FDCore::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>,
                 decltype(std::declval<T>() + std::declval<FDCore::FloatValue::FloatType>())>
  operator+(const T &value, const FDCore::FloatValue &other)
{
    return value + static_cast<FDCore::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator-=(
  T &value, const FDCore::FloatValue &other)
{
    return value -= static_cast<FDCore::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>,
                 decltype(std::declval<T>() + std::declval<FDCore::FloatValue::FloatType>())>
  operator-(const T &value, const FDCore::FloatValue &other)
{
    return value - static_cast<FDCore::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator*=(
  T &value, const FDCore::FloatValue &other)
{
    return value *= static_cast<FDCore::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>,
                 decltype(std::declval<T>() + std::declval<FDCore::FloatValue::FloatType>())>
  operator*(const T &value, const FDCore::FloatValue &other)
{
    return value * static_cast<FDCore::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator/=(
  T &value, const FDCore::FloatValue &other)
{
    return value /= static_cast<FDCore::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>,
                 decltype(std::declval<T>() + std::declval<FDCore::FloatValue::FloatType>())>
  operator/(const T &value, const FDCore::FloatValue &other)
{
    return value / static_cast<FDCore::FloatValue::FloatType>(other);
}

template<typename StreamType>
StreamType &operator<<(StreamType &stream, const FDCore::FloatValue &value)
{
    stream << static_cast<const FDCore::FloatValue::FloatType &>(value);
    return stream;
}

template<typename StreamType>
StreamType &operator>>(StreamType &stream, FDCore::FloatValue &value)
{
    FDCore::FloatValue::FloatType tmp = NAN;
    stream >> tmp;
    value = tmp;
    return stream;
}

#endif // FDCORE_FLOATVALUE_H
