#ifndef FDCORE_ARRAYVALUE_H
#define FDCORE_ARRAYVALUE_H

#ifndef FDCORE_CONTAINER_TYPE
    #include <vector>
    #define FDCORE_CONTAINER_TYPE std::vector
#endif // FDCORE_CONTAINER_TYPE

#include <iterator>
#include <optional>

#include <FDCore/DynamicVariable/AbstractArrayValue.h>

namespace FDCore
{
    class ArrayValue : public AbstractArrayValue
    {
      public:
        typedef FDCORE_CONTAINER_TYPE<AbstractValue::Ptr> ArrayType;

      private:
        ArrayType m_values;

      public:
        ArrayValue() = default;
        ArrayValue(ArrayValue &&) = default;
        ArrayValue(const ArrayValue &) = default;
        ArrayValue(ArrayType &&values) : m_values(std::move(values)) {}
        ArrayValue(const ArrayType &values) : m_values(values) {}

        ArrayValue(std::initializer_list<AbstractValue::Ptr> l) : m_values(l) {}

        ~ArrayValue() override = default;

        explicit operator const ArrayType &() const { return m_values; }

        SizeType size() const override { return m_values.size(); }
        bool isEmpty() const override { return m_values.empty(); }
        AbstractValue::Ptr operator[](SizeType pos) override { return m_values[pos]; }
        const AbstractValue::Ptr &operator[](SizeType pos) const override { return m_values[pos]; }

        void push(AbstractValue::Ptr value) override { m_values.push_back(std::move(value)); }
        AbstractValue::Ptr pop() override;
        void insert(AbstractValue::Ptr value, SizeType pos) override;
        AbstractValue::Ptr removeAt(SizeType pos) override;
        void clear() override { m_values.clear(); }
    };

    template<template<typename> typename Container, typename T>
    struct is_AbstractValue_constructible<Container<T>,
                                          std::enable_if_t<is_AbstractValue_constructible_v<T>, T>>
    {
        constexpr static bool value = true;

        static AbstractValue::Ptr toValue(const Container<T> &value)
        {
            auto arr = std::make_unique<ArrayValue>(new ArrayValue(value));
            for(const auto &cell: value)
                arr->push(is_AbstractValue_constructible<T>::toValue(cell));

            return AbstractValue::Ptr(arr.release());
        }

        static std::optional<T> fromValue(const AbstractValue::Ptr &value)
        {
            if(!value->isType(ValueType::Array))
                return std::nullopt;

            Container<T> result;
            const ArrayValue &arr = static_cast<const ArrayValue &>(*value);
            std::back_insert_iterator<Container<T>> it(result);
            for(ArrayValue::SizeType i = 0, imax = arr.size(); i < imax; ++i)
            {
                std::optional<T> current = is_AbstractValue_constructible<T>::fromValue(arr[i]);
                if(!current.has_value())
                    return std::nullopt;

                it = *current;
            }

            return result;
        }
    };
} // namespace FDCore


#endif // FDCORE_ARRAYVALUE_H
