#include <FDCore/DynamicVariable/BoolValue.h>
#include <FDCore/DynamicVariable/DynamicVariable.h>
#include <FDCore/DynamicVariable/FloatValue.h>
#include <FDCore/DynamicVariable/IntValue.h>
#include <FDCore/DynamicVariable/StringValue.h>

using namespace FDCore;

FDCore::DynamicVariable::DynamicVariable() {}


FDCore::DynamicVariable::DynamicVariable(FDCore::ValueType type)
{
    switch(type)
    {
        case ValueType::Boolean:
            m_value = std::make_shared<BoolValue>();
            break;

        case ValueType::Integer:
            m_value = std::make_shared<IntValue>();
            break;

        case ValueType::Float:
            m_value = std::make_shared<FloatValue>();
            break;

        case ValueType::String:
            m_value = std::make_shared<StringValue>();
            break;

        default:
            break;
    }
}
