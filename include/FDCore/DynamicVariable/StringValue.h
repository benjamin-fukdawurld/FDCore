#ifndef FDCORE_STRINGVALUE_H
#define FDCORE_STRINGVALUE_H

#ifndef FDCORE_STRING_TYPE
    #include <string>
    #include <string_view>
    #ifndef FDCORE_USE_WIDE_STRING
        #define FDCORE_STRING_TYPE std::string
        #define FDCORE_STRING_VIEW_TYPE std::string_view
    #else
        #define FDCORE_STRING_TYPE std::wstring
        #define FDCORE_STRING_VIEW_TYPE std::wstring_view
    #endif // FDCORE_USE_WIDE_STRING
#endif     // FDCORE_STRING_TYPE

#include <FDCore/DynamicVariable/AbstractValue.h>
#include <utility>

namespace FDCore
{
    class StringValue : public AbstractValue
    {
      public:
        typedef FDCORE_STRING_TYPE StringType;
        typedef FDCORE_STRING_VIEW_TYPE StringViewType;
        typedef size_t SizeType;

      private:
        StringType m_value;

      public:
        StringValue() = default;
        StringValue(StringValue &&) = default;
        StringValue(const StringValue &) = default;
        explicit StringValue(StringViewType value) : m_value(value) {}

        ~StringValue() noexcept override = default;

        ValueType getValueType() const override { return ValueType::String; }

        StringValue &operator=(StringValue &&) = default;
        StringValue &operator=(const StringValue &) = default;

        explicit operator const StringType &() const { return m_value; }

        StringValue &operator=(StringViewType value)
        {
            m_value = value;
            return *this;
        }

        bool operator==(const StringValue &value) const { return m_value == value.m_value; }

        bool operator==(StringViewType value) const { return m_value == value; }

        bool operator!=(const StringValue &value) const { return m_value != value.m_value; }

        bool operator!=(StringType value) const { return m_value != value; }

        StringValue &operator+=(StringViewType value)
        {
            m_value += value;
            return *this;
        }

        StringValue operator+(StringViewType value) const
        {
            return StringValue(m_value + value.data());
        }

        SizeType size() const { return m_value.size(); }
        bool isEmpty() const { return m_value.empty(); }

        StringType::value_type &operator[](size_t pos) { return m_value[pos]; }

        const StringType::value_type &operator[](size_t pos) const { return m_value[pos]; }

        void clear() { m_value.clear(); }

        void append(StringViewType str) { m_value.append(str); }
        StringValue subString(SizeType from, SizeType count)
        {
            return StringValue(m_value.substr(from, count));
        }
    };

    template<>
    struct is_AbstractValue_constructible<StringValue::StringType>
    {
        constexpr static bool value = true;

        static AbstractValue::Ptr toValue(const StringValue::StringType &value)
        {
            return AbstractValue::Ptr(new StringValue(value));
        }

        static std::optional<StringValue::StringType> fromValue(const AbstractValue::Ptr &value)
        {
            if(value->isType(ValueType::String))
                return static_cast<StringValue::StringType>(
                  static_cast<const StringValue &>(*value));

            return std::nullopt;
        }
    };
} // namespace FDCore

inline bool operator==(const FDCore::StringValue::StringType &value,
                       const FDCore::StringValue &other)
{
    return value == static_cast<FDCore::StringValue::StringType>(other);
}

inline bool operator!=(const FDCore::StringValue::StringType &value,
                       const FDCore::StringValue &other)
{
    return value == static_cast<FDCore::StringValue::StringType>(other);
}

inline FDCore::StringValue::StringType &operator+=(FDCore::StringValue::StringType &value,
                                                   const FDCore::StringValue &other)
{
    return value += static_cast<FDCore::StringValue::StringType>(other);
}

inline FDCore::StringValue::StringType operator+(const FDCore::StringValue::StringType &value,
                                                 const FDCore::StringValue &other)
{
    return value + static_cast<FDCore::StringValue::StringType>(other);
}

template<typename StreamType>
StreamType &operator<<(StreamType &stream, const FDCore::StringValue &value)
{
    stream << static_cast<FDCore::StringValue::StringType>(value);
    return stream;
}

template<typename StreamType>
StreamType &operator>>(StreamType &stream, FDCore::StringValue &value)
{
    FDCore::StringValue::StringType tmp;
    stream >> tmp;
    value = tmp;
    return stream;
}

#endif // FDCORE_STRINGVALUE_H
