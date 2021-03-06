#ifndef FDCORE_DYNAMICVARIABLE_FWD_H
#define FDCORE_DYNAMICVARIABLE_FWD_H

#include <algorithm>
#include <memory>
#include <stdexcept>

#include <FDCore/DynamicVariable/AbstractArrayValue.h>
#include <FDCore/DynamicVariable/AbstractObjectValue.h>
#include <FDCore/DynamicVariable/AbstractValue.h>
#include <FDCore/DynamicVariable/ArrayValue.h>
#include <FDCore/DynamicVariable/BoolValue.h>
#include <FDCore/DynamicVariable/FloatValue.h>
#include <FDCore/DynamicVariable/IntValue.h>
#include <FDCore/DynamicVariable/ObjectValue.h>
#include <FDCore/DynamicVariable/StringValue.h>

namespace FDCore
{
    template<typename T, bool B = is_AbstractValue_constructible_v<T>>
    struct is_DynamicVariable_constructible;

    class DynamicVariable
    {
      public:
        typedef IntValue::IntType IntType;
        typedef FloatValue::FloatType FloatType;
        typedef StringValue::StringType StringType;
        typedef StringValue::StringViewType StringViewType;
        typedef ArrayValue::ArrayType ArrayType;
        typedef ArrayValue::SizeType SizeType;

      private:
        AbstractValue::Ptr m_value;

      public:
        DynamicVariable();
        DynamicVariable(const DynamicVariable &);
        DynamicVariable(DynamicVariable &&) = default;
        DynamicVariable(ValueType type);
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


        DynamicVariable(StringViewType value) : m_value(std::make_shared<StringValue>(value)) {}

        template<typename T,
                 typename U = std::enable_if_t<is_DynamicVariable_constructible<T>::value,
                                               is_DynamicVariable_constructible<T>>>
        explicit DynamicVariable(const T &value, U /*unused*/ = {});

        explicit DynamicVariable(const ArrayType &value) :
            m_value(std::make_shared<ArrayValue>(value))
        {
        }

        explicit DynamicVariable(ArrayType &&value) :
            m_value(std::make_shared<ArrayValue>(std::move(value)))
        {
        }

        explicit DynamicVariable(std::initializer_list<AbstractValue::Ptr> l) :
            m_value(std::make_shared<ArrayValue>(l))
        {
        }

        explicit DynamicVariable(std::initializer_list<DynamicVariable> l) : DynamicVariable()
        {
            ArrayType arr(l.size());
            std::transform(l.begin(), l.end(), arr.begin(),
                           [](const DynamicVariable &var) { return var.m_value; });
            m_value = std::make_shared<ArrayValue>(std::move(arr));
        }

        virtual ~DynamicVariable() = default;

        ValueType getValueType() const
        {
            return !m_value ? ValueType::None : m_value->getValueType();
        }

        bool isType(ValueType type) const { return type == getValueType(); }

        SizeType size() const;
        bool isEmpty() const;
        DynamicVariable operator[](SizeType pos);
        DynamicVariable operator[](StringViewType member);

        DynamicVariable get(StringViewType member);
        void set(StringViewType key, DynamicVariable value);
        void unset(StringViewType key);

        void push(const DynamicVariable &value);
        DynamicVariable pop();

        void insert(const DynamicVariable &value, SizeType pos);
        DynamicVariable removeAt(SizeType pos);
        void clear();

        void append(const DynamicVariable &str) { append(static_cast<StringType>(str)); };
        void append(StringViewType str);
        DynamicVariable subString(SizeType from, SizeType count);

        DynamicVariable &operator=(const DynamicVariable &) = default;
        DynamicVariable &operator=(DynamicVariable &&) = default;

        DynamicVariable &operator=(StringViewType str);

        DynamicVariable &operator=(ArrayType &&arr);
        DynamicVariable &operator=(const ArrayType &arr);

        template<typename T>
        std::enable_if_t<is_DynamicVariable_constructible<T>::value, DynamicVariable> &operator=(
          const T &value);

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

        bool operator==(StringViewType value) const;

        bool operator!=(StringViewType value) const;

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

        DynamicVariable &operator+=(StringViewType value);

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

        DynamicVariable operator+(StringViewType value) const;

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
                throw generateCastException(__func__);
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
                return DynamicVariable(toInteger() ^ value.toInteger());
            }
            else if(isType(ValueType::Boolean))
            {
                return DynamicVariable(toBool() ^ value.toBool());
            }
            else
            {
                throw generateCastException(__func__);
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

        AbstractValue::Ptr internalValue() { return m_value; }

      private:
        std::runtime_error generateCastException(const std::string &caller) const
        {
            return std::runtime_error(caller + ": unsupported action on type " +
                                      std::to_string(getValueType()));
        }

        BoolValue &toBool()
        {
            if(!isType(ValueType::Boolean))
                throw generateCastException(__func__);

            return static_cast<BoolValue &>(*m_value);
        }


        const BoolValue &toBool() const
        {
            if(!isType(ValueType::Boolean))
                throw generateCastException(__func__);

            return static_cast<BoolValue &>(*m_value);
        }

        IntValue &toInteger()
        {
            if(!isType(ValueType::Integer))
                throw generateCastException(__func__);

            return static_cast<IntValue &>(*m_value);
        }


        const IntValue &toInteger() const
        {
            if(!isType(ValueType::Integer))
                throw generateCastException(__func__);

            return static_cast<IntValue &>(*m_value);
        }

        FloatValue &toFloat()
        {
            if(!isType(ValueType::Float))
                throw generateCastException(__func__);

            return static_cast<FloatValue &>(*m_value);
        }


        const FloatValue &toFloat() const
        {
            if(!isType(ValueType::Float))
                throw generateCastException(__func__);

            return static_cast<FloatValue &>(*m_value);
        }

        StringValue &toString()
        {
            if(!isType(ValueType::String))
                throw generateCastException(__func__);

            return static_cast<StringValue &>(*m_value);
        }

        const StringValue &toString() const
        {
            if(!isType(ValueType::String))
                throw generateCastException(__func__);

            return static_cast<StringValue &>(*m_value);
        }

        AbstractArrayValue &toArray()
        {
            if(!isType(ValueType::Array))
                throw generateCastException(__func__);

            return static_cast<AbstractArrayValue &>(*m_value);
        }

        const AbstractArrayValue &toArray() const
        {
            if(!isType(ValueType::Array))
                throw generateCastException(__func__);

            return static_cast<AbstractArrayValue &>(*m_value);
        }

        AbstractObjectValue &toObject()
        {
            if(!isType(ValueType::Object))
                throw generateCastException(__func__);

            return static_cast<AbstractObjectValue &>(*m_value);
        }

        const AbstractObjectValue &toObject() const
        {
            if(!isType(ValueType::Object))
                throw generateCastException(__func__);

            return static_cast<AbstractObjectValue &>(*m_value);
        }

        template<typename T>
        void convert(
          std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &result) const;

        template<typename T>
        void convert(std::enable_if_t<std::is_floating_point_v<T>, T> &result) const;
    };

    template<typename T>
    struct is_DynamicVariable_constructible<T, false>
    {
        constexpr static bool value = false;
    };

    template<typename T>
    struct is_DynamicVariable_constructible<T, true>
    {
        constexpr static bool value = true;

        static DynamicVariable toVariable(const T &value)
        {
            return DynamicVariable(is_AbstractValue_constructible<T>::toValue(value));
        }

        static std::optional<T> fromVariable(const AbstractValue::Ptr &value)
        {
            return is_AbstractValue_constructible<T>::fromValue(value);
        }
    };

    template<class T>
    inline constexpr bool is_DynamicVariable_constructible_v =
      is_DynamicVariable_constructible<T>::value;
} // namespace FDCore

#endif // FDCORE_DYNAMICVARIABLE_FWD_H
