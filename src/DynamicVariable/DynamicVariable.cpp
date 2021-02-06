#include <FDCore/DynamicVariable/DynamicVariable.h>
#include <utility>

using namespace FDCore;

FDCore::DynamicVariable::DynamicVariable() {}


FDCore::DynamicVariable::DynamicVariable(FDCore::ValueType type)
{
    switch(type)
    {
        case FDCore::ValueType::Boolean:
            m_value = std::make_shared<FDCore::BoolValue>();
            break;

        case FDCore::ValueType::Integer:
            m_value = std::make_shared<FDCore::IntValue>();
            break;

        case FDCore::ValueType::Float:
            m_value = std::make_shared<FDCore::FloatValue>();
            break;

        case FDCore::ValueType::String:
            m_value = std::make_shared<FDCore::StringValue>();
            break;

        default:
            break;
    }
}


FDCore::DynamicVariable &FDCore::DynamicVariable::operator=(FDCore::StringValue::StringType &&str)
{
    m_value = std::make_shared<FDCore::StringValue>(std::move(str));
    return *this;
}

FDCore::DynamicVariable &FDCore::DynamicVariable::operator=(
  const FDCore::StringValue::StringType &str)
{
    m_value = std::make_shared<FDCore::StringValue>(str);
    return *this;
}

FDCore::DynamicVariable &FDCore::DynamicVariable::operator=(bool value)
{
    m_value = std::make_shared<FDCore::BoolValue>(value);
    return *this;
}
