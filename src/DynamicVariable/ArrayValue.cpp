#include <FDCore/DynamicVariable/ArrayValue.h>

void FDCore::ArrayValue::insert(FDCore::AbstractValue::Ptr value, FDCore::ArrayValue::SizeType pos)
{
    auto where = m_values.begin();
    std::advance(where, pos);
    m_values.insert(where, std::move(value));
}

FDCore::AbstractValue::Ptr FDCore::ArrayValue::removeAt(FDCore::ArrayValue::SizeType pos)
{
    AbstractValue::Ptr result = m_values[pos];
    auto where = m_values.begin();
    std::advance(where, pos);
    m_values.erase(where);
    return result;
}

FDCore::AbstractValue::Ptr FDCore::ArrayValue::pop()
{
    FDCore::AbstractValue::Ptr result = m_values.back();
    m_values.pop_back();
    return result;
}
