#ifndef FDCORE_ARRAYVALUE_H
#define FDCORE_ARRAYVALUE_H

#ifndef FDCORE_CONTAINER_TYPE
    #include <vector>
    #define FDCORE_CONTAINER_TYPE std::vector
#endif // FDCORE_CONTAINER_TYPE

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
} // namespace FDCore


#endif // FDCORE_ARRAYVALUE_H
