#ifndef FDCORE_ABSTRACTVALUE_H
#define FDCORE_ABSTRACTVALUE_H

#include <FDCore/DynamicVariable/ValueType.h>
#include <memory>

namespace FDCore
{
    template<typename T, typename U = void>
    struct is_AbstractValue_constructible
    {
        constexpr static bool value = false;
    };

    template<class T>
    inline constexpr bool is_AbstractValue_constructible_v =
      is_AbstractValue_constructible<T>::value;

    class AbstractValue
    {
      public:
        typedef std::shared_ptr<AbstractValue> Ptr;


        AbstractValue() = default;
        AbstractValue(AbstractValue &&) = default;
        AbstractValue(const AbstractValue &) = default;

        virtual ~AbstractValue() noexcept = default;

        AbstractValue &operator=(AbstractValue &&) = default;
        AbstractValue &operator=(const AbstractValue &) = default;

        virtual ValueType getValueType() const = 0;
        virtual bool isType(ValueType type) const { return type == getValueType(); }
    };
} // namespace FDCore

#endif // FDCORE_ABSTRACTVALUE_H
