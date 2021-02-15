#ifndef FDCORE_OBJECTVALUE_H
#define FDCORE_OBJECTVALUE_H

#ifndef FDCORE_MAP_TYPE
    #include <unordered_map>
    #define FDCORE_MAP_TYPE std::unordered_map
#endif // FDCORE_MAP_TYPE

#include <FDCore/DynamicVariable/AbstractValue.h>

namespace FDCore
{
    class ObjectValue : public AbstractObjectValue
    {
      public:
        typedef FDCORE_MAP_TYPE<StringType, AbstractValue::Ptr> ObjectType;

      private:
        ObjectType m_values;

      public:
        ObjectValue() = default;
        ObjectValue(ObjectValue &&) = default;
        ObjectValue(const ObjectValue &) = default;

        ~ObjectValue() override = default;

        AbstractValue::Ptr operator[](StringViewType member) override
        {
            auto it = m_values.find(StringType(member));
            if(it == m_values.end())
                return AbstractValue::Ptr();

            return it->second;
        }

        const AbstractValue::Ptr operator[](StringViewType member) const override
        {
            auto it = m_values.find(StringType(member));
            if(it == m_values.end())
                return AbstractValue::Ptr();

            return it->second;
        }

        void set(StringViewType key, AbstractValue::Ptr value) override
        {
            m_values[StringType(key)] = value;
        }

        void unset(StringViewType key) override { m_values.erase(StringType(key)); }
    };
} // namespace FDCore

#endif // FDCORE_OBJECTVALUE_H