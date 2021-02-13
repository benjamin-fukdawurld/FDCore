#ifndef FDCORE_DYNAMICVARIABLE_H
#define FDCORE_DYNAMICVARIABLE_H

#include <FDCore/DynamicVariable/DynamicVariable_conversion.h>
#include <FDCore/DynamicVariable/DynamicVariable_fwd.h>
#include <math.h>

namespace FDCore
{
    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator=(const T &value)
    {
        m_value = std::make_shared<FDCore::IntValue>(value);
        return *this;
    }

    template<typename T>
    std::enable_if_t<std::is_floating_point_v<T>, DynamicVariable> &DynamicVariable::operator=(
      const T &value)
    {
        m_value = std::make_shared<FDCore::FloatValue>(value);
        return *this;
    }

    template<typename T>
    void DynamicVariable::convert(
      std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &result) const
    {
        assert(isType(ValueType::Integer) || isType(ValueType::Float));
        if(getValueType() == ValueType::Integer)
        {
            result = static_cast<T>(toInteger());
        }

        result = static_cast<T>(toFloat());
    }

    template<typename T>
    void DynamicVariable::convert(std::enable_if_t<std::is_floating_point_v<T>, T> &result) const
    {
        assert(isType(ValueType::Integer) || isType(ValueType::Float));
        if(getValueType() == ValueType::Integer)
        {
            result = static_cast<T>(static_cast<IntType>(toInteger()));
        }

        result = static_cast<T>(toFloat());
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator==(const T &value) const
    {
        assert(isType(ValueType::Integer) || isType(ValueType::Float));
        if(getValueType() == ValueType::Integer)
        {
            return toInteger() == value;
        }

        return toFloat() == value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator==(const T &value) const
    {
        assert(isType(ValueType::Float));
        return toFloat() == value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator!=(const T &value) const
    {
        assert(isType(ValueType::Integer) || isType(ValueType::Float));
        if(getValueType() == ValueType::Integer)
        {
            return toInteger() != value;
        }

        return toFloat() != value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator!=(const T &value) const
    {
        assert(isType(ValueType::Float));
        return toFloat() != value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator<=(const T &value) const
    {
        assert(isType(ValueType::Integer) || isType(ValueType::Float));
        if(getValueType() == ValueType::Integer)
        {
            return toInteger() <= value;
        }

        return toFloat() <= value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator<=(const T &value) const
    {
        assert(isType(ValueType::Float));
        return toFloat() <= value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator<(const T &value) const
    {
        assert(isType(ValueType::Integer) || isType(ValueType::Float));
        if(getValueType() == ValueType::Integer)
        {
            return toInteger() < value;
        }

        return toFloat() < value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator<(const T &value) const
    {
        assert(isType(ValueType::Float));
        return toFloat() < value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator>=(const T &value) const
    {
        assert(isType(ValueType::Integer) || isType(ValueType::Float));
        if(getValueType() == ValueType::Integer)
        {
            return toInteger() >= value;
        }

        return toFloat() >= value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator>=(const T &value) const
    {
        assert(isType(ValueType::Float));
        return toFloat() >= value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator>(const T &value) const
    {
        assert(isType(ValueType::Integer) || isType(ValueType::Float));
        if(getValueType() == ValueType::Integer)
        {
            return toInteger() > value;
        }

        return toFloat() > value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator>(const T &value) const
    {
        assert(isType(ValueType::Float));
        return toFloat() > value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator+=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
            {
                toInteger() += value;
                return *this;
            }

            case ValueType::Float:
            {
                toFloat() += static_cast<FloatType>(value);
                return *this;
            }

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      &DynamicVariable::operator+=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                *this = FDCore::FloatValue(static_cast<IntType>(toInteger()) + value);
                return *this;

            case ValueType::Float:
                toFloat() += value;
                return *this;

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator-=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
            {
                toInteger() -= value;
                return *this;
            }

            case ValueType::Float:
            {
                toFloat() -= static_cast<FloatType>(value);
                return *this;
            }

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      &DynamicVariable::operator-=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                *this = FDCore::FloatValue(static_cast<IntType>(toInteger()) - value);
                return *this;

            case ValueType::Float:
                toFloat() -= value;
                return *this;

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      DynamicVariable::operator+(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return toInteger() + value;
            case ValueType::Float:
                return toFloat() + static_cast<FloatType>(value);

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      DynamicVariable::operator+(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return FDCore::FloatValue(static_cast<IntType>(toInteger()) + value);

            case ValueType::Float:
                return toFloat() + value;

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      DynamicVariable::operator-(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return toInteger() - value;

            case ValueType::Float:
                return toFloat() - static_cast<FloatType>(value);

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      DynamicVariable::operator-(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return FDCore::FloatValue(static_cast<IntType>(toInteger()) - value);

            case ValueType::Float:
                return toFloat() - value;

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator%=(const T &value)
    {
        assert(isType(ValueType::Integer));
        toInteger() %= value;
        return *this;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      DynamicVariable::operator%(const T &value) const
    {
        assert(isType(ValueType::Integer));
        return toInteger() % value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator*=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
            {
                toInteger() *= value;
                return *this;
            }

            case ValueType::Float:
            {
                toFloat() *= static_cast<FloatType>(value);
                return *this;
            }

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      &DynamicVariable::operator*=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                *this = FDCore::FloatValue(static_cast<IntType>(toInteger()) * value);
                return *this;

            case ValueType::Float:
                toFloat() *= value;
                return *this;

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      DynamicVariable::operator*(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return toInteger() * value;

            case ValueType::Float:
                return toFloat() * static_cast<FloatType>(value);

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      DynamicVariable::operator*(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return FDCore::FloatValue(static_cast<IntType>(toInteger()) * value);

            case ValueType::Float:
                return toFloat() * value;

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator/=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
            {
                toInteger() /= value;
                return *this;
            }

            case ValueType::Float:
            {
                toFloat() /= static_cast<FloatType>(value);
                return *this;
            }

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      &DynamicVariable::operator/=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                *this = FDCore::FloatValue(static_cast<IntType>(toInteger()) / value);
                return *this;

            case ValueType::Float:
                toFloat() /= value;
                return *this;

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      DynamicVariable::operator/(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return toInteger() / value;

            case ValueType::Float:
                return toFloat() / static_cast<FloatType>(value);

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      DynamicVariable::operator/(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return FDCore::FloatValue(static_cast<IntType>(toInteger()) / value);

            case ValueType::Float:
                return toFloat() / value;

            default:
                assert("Unsupported operation");
                return *this;
        }
    }

    DynamicVariable operator""_var(unsigned long long value) { return DynamicVariable(value); }

    DynamicVariable operator""_var(long double value) { return DynamicVariable(value); }

    DynamicVariable operator""_var(const DynamicVariable::StringType::value_type *value,
                                   size_t size)
    {
        return DynamicVariable(DynamicVariable::StringType(value, size));
    }

    template<typename StreamType, typename U>
    void DynamicVariable::read(StreamType &stream)
    {
        switch(getValueType())
        {
            case FDCore::ValueType::Boolean:
            {
                bool tmp = 0;
                stream >> tmp;
                *this = tmp;
                break;
            }

            case FDCore::ValueType::Integer:
            {
                FDCore::DynamicVariable::IntType tmp = 0;
                stream >> tmp;
                *this = tmp;
                break;
            }

            case FDCore::ValueType::Float:
            {
                FDCore::DynamicVariable::FloatType tmp = NAN;
                stream >> tmp;
                *this = tmp;
                break;
            }

            default:
                break;
        }
    }

    template<typename StreamType, typename U>
    void DynamicVariable::write(StreamType &stream) const
    {
        switch(getValueType())
        {
            case FDCore::ValueType::Boolean:
                stream << toBool();
                break;

            case FDCore::ValueType::Integer:
                stream << toInteger();
                break;

            case FDCore::ValueType::Float:
                stream << toFloat();
                break;

            default:
                break;
        }
    }

} // namespace FDCore

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator==(
  const T &value, const FDCore::DynamicVariable &other)
{
    return other == value;
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator!=(
  const T &value, const FDCore::DynamicVariable &other)
{
    return other != value;
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<=(
  const T &value, const FDCore::DynamicVariable &other)
{
    return value <= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<(
  const T &value, const FDCore::DynamicVariable &other)
{
    return value < static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>=(
  const T &value, const FDCore::DynamicVariable &other)
{
    return value >= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>(
  const T &value, const FDCore::DynamicVariable &other)
{
    return value > static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator+=(
  T &value, const FDCore::DynamicVariable &other)
{
    return value += static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator-=(
  T &value, const FDCore::DynamicVariable &other)
{
    return value -= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator+(
  const T &value, const FDCore::DynamicVariable &other)
{
    return value + static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator-(
  const T &value, const FDCore::DynamicVariable &other)
{
    return value - static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator*=(
  T &value, const FDCore::DynamicVariable &other)
{
    return value *= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator/=(
  T &value, const FDCore::DynamicVariable &other)
{
    return value /= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator*(
  const T &value, const FDCore::DynamicVariable &other)
{
    return value * static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator/(
  const T &value, const FDCore::DynamicVariable &other)
{
    return value / static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator%=(
  T &value, const FDCore::DynamicVariable &other)
{
    return value %= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator%(
  const T &value, const FDCore::DynamicVariable &other)
{
    return value % static_cast<T>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> operator<<=(const T &value,
                                                       const FDCore::DynamicVariable &other)
{
    return value <<= static_cast<const FDCore::DynamicVariable::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> operator<<(const T &value,
                                                      const FDCore::DynamicVariable &other)
{
    return value << static_cast<const FDCore::DynamicVariable::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> &operator>>=(const T &value,
                                                        FDCore::DynamicVariable &other)
{

    return value >>= static_cast<const FDCore::DynamicVariable::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> &operator>>(const T &value,
                                                       FDCore::DynamicVariable &other)
{

    return value >> static_cast<const FDCore::DynamicVariable::IntType &>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator&=(
  T &value, FDCore::DynamicVariable &other)
{
    return value &= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator&(
  const T &value, FDCore::DynamicVariable &other)
{
    return value & static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator|=(
  T &value, FDCore::DynamicVariable &other)
{
    return value |= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator|(
  const T &value, FDCore::DynamicVariable &other)
{
    return value | static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator^=(
  T &value, FDCore::DynamicVariable &other)
{
    return value ^= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator^(
  const T &value, FDCore::DynamicVariable &other)
{
    return value ^ static_cast<T>(other);
}

std::basic_ostream<FDCore::DynamicVariable::StringType::value_type> &operator<<(
  std::basic_ostream<FDCore::DynamicVariable::StringType::value_type> &stream,
  const FDCore::DynamicVariable &value)
{
    value.write<std::basic_ostream<FDCore::DynamicVariable::StringType::value_type>>(stream);
    return stream;
}

std::basic_istream<FDCore::DynamicVariable::StringType::value_type> &operator>>(
  std::basic_istream<FDCore::DynamicVariable::StringType::value_type> &stream,
  FDCore::DynamicVariable &value)
{
    value.read<std::basic_istream<FDCore::DynamicVariable::StringType::value_type>>(stream);
    return stream;
}

#endif // FDCORE_DYNAMICVARIABLE_H
