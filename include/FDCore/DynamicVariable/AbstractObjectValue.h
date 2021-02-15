#ifndef FDCORE_ABSTRACTOBJECTVALUE_H
#define FDCORE_ABSTRACTOBJECTVALUE_H

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

namespace FDCore
{
    class AbstractObjectValue : public AbstractValue
    {
      public:
        typedef FDCORE_STRING_TYPE StringType;
        typedef FDCORE_STRING_VIEW_TYPE StringViewType;

        AbstractObjectValue() = default;
        AbstractObjectValue(AbstractObjectValue &&) = default;
        AbstractObjectValue(const AbstractObjectValue &) = default;

        virtual ~AbstractObjectValue() = default;

        virtual AbstractValue::Ptr operator[](StringViewType member) = 0;
        virtual const AbstractValue::Ptr operator[](StringViewType member) const = 0;

        virtual AbstractValue::Ptr get(StringViewType member) { return operator[](member); }
        virtual const AbstractValue::Ptr get(StringViewType member) const
        {
            return operator[](member);
        }

        virtual void set(StringViewType key, AbstractValue::Ptr value) = 0;
        virtual void unset(StringViewType key) = 0;

        ValueType getValueType() const override { return ValueType::Object; }
    };
} // namespace FDCore

#endif // FDCORE_ABSTRACTOBJECTVALUE_H