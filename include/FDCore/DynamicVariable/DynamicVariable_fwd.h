#ifndef FDCORE_DYNAMICVARIABLE_FWD_H
#define FDCORE_DYNAMICVARIABLE_FWD_H

#include <FDCore/DynamicVariable/AbstractArrayValue.h>
#include <FDCore/DynamicVariable/AbstractValue.h>
#include <FDCore/DynamicVariable/ArrayValue.h>
#include <FDCore/DynamicVariable/BoolValue.h>
#include <FDCore/DynamicVariable/FloatValue.h>
#include <FDCore/DynamicVariable/IntValue.h>
#include <FDCore/DynamicVariable/StringValue.h>
#include <algorithm>
#include <cassert>
#include <memory>

namespace FDCore
{
    template<typename T, typename U = void>
    struct DynamicVariableConverter
    {
        constexpr static bool isConvertibe = false;
    };

    class DynamicVariable
    {
      public:
        typedef IntValue::IntType IntType;
        typedef FloatValue::FloatType FloatType;
        typedef StringValue::StringType StringType;
        typedef ArrayValue::ArrayType ArrayType;
        typedef ArrayValue::SizeType SizeType;

      private:
        AbstractValue::Ptr m_value;

      public:
        DynamicVariable();
        DynamicVariable(ValueType type);
        DynamicVariable(const DynamicVariable &) = default;
        DynamicVariable(DynamicVariable &&) = default;
        DynamicVariable(const AbstractValue::Ptr &value);
        DynamicVariable(AbstractValue::Ptr &&value);

        template<typename T, typename U = std::enable_if_t<std::is_base_of_v<AbstractValue, T>, T>>
        DynamicVariable(const T &value) : m_value(std::make_shared<T>(value))
        {
        }

        template<typename T, typename U = std::enable_if_t<std::is_base_of_v<AbstractValue, T>, T>>
        DynamicVariable(T &&value) : m_value(std::make_shared<T>(std::forward<T>(value)))
        {
        }

        DynamicVariable(bool value) : m_value(std::make_shared<BoolValue>(value)) {}

        DynamicVariable(const StringType &value) : m_value(std::make_shared<StringValue>(value)) {}

        DynamicVariable(StringType &&value) :
            m_value(std::make_shared<StringValue>(std::move(value)))
        {
        }

        DynamicVariable(const ArrayType &value) : m_value(std::make_shared<ArrayValue>(value)) {}

        DynamicVariable(ArrayType &&value) : m_value(std::make_shared<ArrayValue>(std::move(value)))
        {
        }

        DynamicVariable(std::initializer_list<AbstractValue::Ptr> l) :
            m_value(std::make_shared<ArrayValue>(l))
        {
        }

        DynamicVariable(std::initializer_list<DynamicVariable> l) : DynamicVariable()
        {
            ArrayType arr(l.size());
            std::transform(l.begin(), l.end(), arr.begin(),
                           [](const DynamicVariable &var) { return var.m_value; });
            m_value = std::make_shared<ArrayValue>(std::move(arr));
        }

        template<typename T>
        DynamicVariable(
          const T &value,
          std::enable_if_t<!std::is_same_v<bool, T> && std::is_integral_v<T>, IntType> /*unused*/
          = {}) :
            m_value(std::make_shared<IntValue>(value))
        {
        }

        template<typename T>
        DynamicVariable(const T &value,
                        std::enable_if_t<std::is_floating_point_v<T>, FloatType> /*unused*/ = {}) :
            m_value(std::make_shared<FloatValue>(value))
        {
        }

        virtual ~DynamicVariable() = default;

        template<typename T>
        static std::enable_if_t<std::is_base_of_v<AbstractValue, T>, DynamicVariable> instantiate()
        {
            DynamicVariable result;
            result.m_value = std::make_shared<T>();
            return result;
        }

        template<typename T, typename... Args>
        static std::enable_if_t<std::is_base_of_v<AbstractValue, T>, DynamicVariable> instantiate(
          Args... args)
        {
            DynamicVariable result;
            result.m_value = std::make_shared<T>(args...);
            return result;
        }

        ValueType getValueType() const
        {
            return !m_value ? ValueType::None : m_value->getValueType();
        }

        bool isType(ValueType type) const { return type == getValueType(); }

        SizeType size() const;
        bool isEmpty() const;
        DynamicVariable operator[](SizeType pos);

        void push(const DynamicVariable &value);
        DynamicVariable pop();

        void insert(const DynamicVariable &value, SizeType pos);
        DynamicVariable removeAt(SizeType pos);
        void clear();

        void append(const DynamicVariable &str) { append(static_cast<StringType>(str)); };
        void append(const StringType &str);
        DynamicVariable subString(SizeType from, SizeType count);

        DynamicVariable &operator=(const DynamicVariable &) = default;
        DynamicVariable &operator=(DynamicVariable &&) = default;

        DynamicVariable &operator=(StringType &&str);
        DynamicVariable &operator=(const StringType &str);

        DynamicVariable &operator=(bool value);

        DynamicVariable &operator=(ArrayType &&arr);
        DynamicVariable &operator=(const ArrayType &arr);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator=(const T &value);

        template<typename T>
        std::enable_if_t<std::is_floating_point_v<T>, DynamicVariable> &operator=(const T &value);

        explicit operator bool() const;
        explicit operator StringType() const;
        explicit operator const StringType &() const;
        explicit operator ArrayType() const;
        explicit operator const ArrayType &() const;

        template<typename T>
        explicit operator T() const
        {
            T result;
            convert<T>(result);
            return result;
        }

        bool operator==(const DynamicVariable &value) const;

        bool operator!=(const DynamicVariable &value) const;

        bool operator==(std::nullptr_t) const;

        bool operator!=(std::nullptr_t) const;

        bool operator==(bool value) const;

        bool operator!=(bool value) const;

        bool operator==(const StringType &value) const;
        bool operator!=(const StringType &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator==(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator==(
          const T &value) const;


        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator!=(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator!=(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<=(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator<=(
          const T &value) const;


        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator<(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>=(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator>=(
          const T &value) const;


        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator>(
          const T &value) const;

        DynamicVariable operator!() const { return !toBool(); }

        bool operator&&(bool other) const { return toBool() && other; }
        bool operator&&(const DynamicVariable &other) const { return toBool() && other.toBool(); }

        bool operator||(bool other) const { return toBool() || other; }
        bool operator||(const DynamicVariable &other) const { return toBool() || other.toBool(); }

        bool operator^(bool other) const { return toBool() ^ other; }

        DynamicVariable operator-() const;

        DynamicVariable operator~() const;

        DynamicVariable operator+() const;

        DynamicVariable &operator++();

        DynamicVariable operator++(int);

        DynamicVariable &operator--();

        DynamicVariable operator--(int);

        DynamicVariable &operator+=(const StringType &value);

        DynamicVariable &operator+=(const DynamicVariable &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator+=(const T &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          &operator+=(const T &value);

        DynamicVariable &operator-=(const DynamicVariable &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator-=(const T &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          &operator-=(const T &value);

        DynamicVariable operator+(const StringType &value) const;

        DynamicVariable operator+(const DynamicVariable &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator+(const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          operator+(const T &value) const;

        DynamicVariable operator-(const DynamicVariable &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator-(const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          operator-(const T &value) const;

        DynamicVariable &operator*=(const DynamicVariable &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator*=(const T &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          &operator*=(const T &value);

        DynamicVariable operator*(const DynamicVariable &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator*(const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          operator*(const T &value) const;

        DynamicVariable &operator/=(const DynamicVariable &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator/=(const T &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          &operator/=(const T &value);

        DynamicVariable operator/(const DynamicVariable &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator/(const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          operator/(const T &value) const;

        DynamicVariable &operator%=(const DynamicVariable &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator%=(const T &value);

        DynamicVariable operator%(const DynamicVariable &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator%(const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator<<=(const T &value)
        {
            toInteger() <<= static_cast<IntType>(value);
            return *this;
        }

        DynamicVariable &operator<<=(const DynamicVariable &value)
        {
            toInteger() <<= value.toInteger();
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator>>=(const T &value)
        {
            toInteger() >>= static_cast<IntType>(value);
            return *this;
        }

        DynamicVariable &operator>>=(const DynamicVariable &value)
        {
            toInteger() >>= value.toInteger();
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator<<(const T &value) const
        {
            return toInteger() << static_cast<IntType>(value);
        }

        DynamicVariable operator<<(const DynamicVariable &value) const
        {
            return toInteger() << value.toInteger();
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator>>(const T &value) const
        {
            return toInteger() >> static_cast<IntType>(value);
        }

        DynamicVariable operator>>(const DynamicVariable &value) const
        {
            return toInteger() >> value.toInteger();
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator&=(const T &value)
        {
            toInteger() &= static_cast<IntType>(value);
            return *this;
        }

        DynamicVariable &operator&=(const DynamicVariable &value)
        {
            toInteger() &= value.toInteger();
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator&(const T &value) const
        {
            return toInteger() & static_cast<IntType>(value);
        }

        DynamicVariable operator&(const DynamicVariable &value) const
        {
            return toInteger() & value.toInteger();
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator|=(const T &value)
        {
            toInteger() |= static_cast<IntType>(value);
            return *this;
        }

        DynamicVariable &operator|=(const DynamicVariable &value)
        {
            toInteger() |= value.toInteger();
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator|(const T &value) const
        {
            return toInteger() | static_cast<IntType>(value);
        }

        DynamicVariable operator|(const DynamicVariable &value) const
        {
            return toInteger() | value.toInteger();
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator^=(const T &value)
        {
            toInteger() ^= static_cast<IntType>(value);
            return *this;
        }

        DynamicVariable &operator^=(const DynamicVariable &value)
        {
            if(isType(ValueType::Integer))
            {
                toInteger() ^= value.toInteger();
            }
            else if(isType(ValueType::Boolean))
            {
                toBool() ^= value.toBool();
            }
            else
            {
                assert("Unsupported action");
            }

            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator^(const T &value) const
        {
            return toInteger() ^ static_cast<IntType>(value);
        }

        DynamicVariable operator^(const DynamicVariable &value) const
        {
            if(isType(ValueType::Integer))
            {
                toInteger() ^ value.toInteger();
            }
            else if(isType(ValueType::Boolean))
            {
                toBool() ^ value.toBool();
            }
            else
            {
                assert("Unsupported action");
            }

            return *this;
        }

        template<typename StreamType,
                 typename U = std::enable_if_t<!std::is_integral_v<StreamType> &&
                                                 !std::is_same_v<DynamicVariable, StreamType>,
                                               StreamType>>
        void read(StreamType &stream);

        template<typename StreamType,
                 typename U = std::enable_if_t<!std::is_integral_v<StreamType> &&
                                                 !std::is_same_v<DynamicVariable, StreamType>,
                                               StreamType>>
        void write(StreamType &stream) const;

      private:
        BoolValue &toBool()
        {
            assert(isType(ValueType::Boolean));
            return static_cast<BoolValue &>(*m_value);
        }


        const BoolValue &toBool() const
        {
            assert(isType(ValueType::Boolean));
            return static_cast<BoolValue &>(*m_value);
        }

        IntValue &toInteger()
        {
            assert(isType(ValueType::Integer));
            return static_cast<IntValue &>(*m_value);
        }


        const IntValue &toInteger() const
        {
            assert(isType(ValueType::Integer));
            return static_cast<IntValue &>(*m_value);
        }

        FloatValue &toFloat()
        {
            assert(isType(ValueType::Float));
            return static_cast<FloatValue &>(*m_value);
        }


        const FloatValue &toFloat() const
        {
            assert(isType(ValueType::Float));
            return static_cast<FloatValue &>(*m_value);
        }

        StringValue &toString()
        {
            assert(isType(ValueType::String));
            return static_cast<StringValue &>(*m_value);
        }

        const StringValue &toString() const
        {
            assert(isType(ValueType::String));
            return static_cast<StringValue &>(*m_value);
        }

        AbstractArrayValue &toArray()
        {
            assert(isType(ValueType::Array));
            return static_cast<AbstractArrayValue &>(*m_value);
        }

        const AbstractArrayValue &toArray() const
        {
            assert(isType(ValueType::Array));
            return static_cast<AbstractArrayValue &>(*m_value);
        }

        template<typename T>
        void convert(
          std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &result) const;

        template<typename T>
        void convert(std::enable_if_t<std::is_floating_point_v<T>, T> &result) const;
    };
} // namespace FDCore

#endif // FDCORE_DYNAMICVARIABLE_FWD_H
