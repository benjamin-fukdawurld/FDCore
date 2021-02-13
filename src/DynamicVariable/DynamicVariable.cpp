#include <FDCore/DynamicVariable/DynamicVariable.h>
#include <utility>

using namespace FDCore;

DynamicVariable::DynamicVariable() {}


DynamicVariable::DynamicVariable(ValueType type)
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

        case ValueType::Array:
            m_value = std::make_shared<ArrayValue>();
            break;

        default:
            break;
    }
}

DynamicVariable::DynamicVariable(const AbstractValue::Ptr &value) : m_value(value) {}

DynamicVariable::DynamicVariable(AbstractValue::Ptr &&value) : m_value(std::move(value)) {}

DynamicVariable &DynamicVariable::operator=(StringType &&str)
{
    m_value = std::make_shared<StringValue>(std::move(str));
    return *this;
}

DynamicVariable &DynamicVariable::operator=(const StringType &str)
{
    m_value = std::make_shared<StringValue>(str);
    return *this;
}

DynamicVariable &DynamicVariable::operator=(bool value)
{
    m_value = std::make_shared<BoolValue>(value);
    return *this;
}

DynamicVariable &DynamicVariable::operator=(ArrayType &&arr)
{
    m_value = std::make_shared<ArrayValue>(std::move(arr));
    return *this;
}

DynamicVariable &DynamicVariable::operator=(const ArrayType &arr)
{
    m_value = std::make_shared<ArrayValue>(arr);
    return *this;
}

DynamicVariable::operator bool() const
{
    assert(isType(ValueType::Boolean));
    return static_cast<bool>(toBool());
}

DynamicVariable::operator const StringType &() const
{
    assert(isType(ValueType::String));
    return static_cast<const StringType &>(toString());
}

DynamicVariable::operator const ArrayType &() const
{
    assert(isType(ValueType::Array));
    return static_cast<const ArrayType &>(static_cast<const ArrayValue &>(toArray()));
}

DynamicVariable::operator StringType() const
{
    assert(isType(ValueType::String));
    return static_cast<StringType>(toString());
}

DynamicVariable::operator ArrayType() const
{
    assert(isType(ValueType::Array));
    return static_cast<ArrayType>(static_cast<const ArrayValue &>(toArray()));
}

bool DynamicVariable::operator==(const DynamicVariable &value) const
{
    ValueType type = getValueType();
    if(type != value.getValueType())
    {
        return false;
    }

    switch(type)
    {
        case ValueType::None:
            return true;

        case ValueType::Boolean:
            return toBool() == value.toBool();

        case ValueType::Integer:
            return toInteger() == value.toInteger();

        case ValueType::Float:
            return toFloat() == value.toFloat();

        case ValueType::String:
            return toString() == value.toString();

        default:
            break;
    }

    return false;
}

bool DynamicVariable::operator!=(const DynamicVariable &value) const
{
    ValueType type = getValueType();
    if(type != value.getValueType())
    {
        return true;
    }

    switch(type)
    {
        case ValueType::None:
            return false;

        case ValueType::Boolean:
            return toBool() != value.toBool();

        case ValueType::Integer:
            return toInteger() != value.toInteger();

        case ValueType::Float:
            return toFloat() != value.toFloat();

        case ValueType::String:
            return toString() != value.toString();

        default:
            break;
    }

    return true;
}

bool DynamicVariable::operator==(std::nullptr_t) const { return isType(ValueType::None); }

bool DynamicVariable::operator!=(std::nullptr_t) const { return !isType(ValueType::None); }

bool DynamicVariable::operator==(bool value) const
{
    return isType(ValueType::Boolean) && toBool() == value;
}

bool DynamicVariable::operator!=(bool value) const
{
    return !isType(ValueType::Boolean) || toBool() != value;
}

bool DynamicVariable::operator==(const StringType &value) const
{
    return isType(ValueType::String) && toString() == value;
}

bool DynamicVariable::operator!=(const StringType &value) const
{
    return !isType(ValueType::String) || toString() != value;
}

DynamicVariable DynamicVariable::operator-() const
{
    assert(isType(ValueType::Integer) || isType(ValueType::Float));
    if(getValueType() == ValueType::Integer)
    {
        return DynamicVariable(-toInteger());
    }

    return DynamicVariable(-toFloat());
}

DynamicVariable DynamicVariable::operator~() const
{
    assert(isType(ValueType::Integer));
    return DynamicVariable(~toInteger());
}

DynamicVariable DynamicVariable::operator+() const
{
    assert(isType(ValueType::Integer) || isType(ValueType::Float));
    if(getValueType() == ValueType::Integer)
    {
        return DynamicVariable(+toInteger());
    }

    return DynamicVariable(+toFloat());
}

DynamicVariable &DynamicVariable::operator++()
{
    assert(isType(ValueType::Integer));
    ++toInteger();
    return *this;
}

DynamicVariable DynamicVariable::operator++(int)
{
    assert(isType(ValueType::Integer));
    return DynamicVariable(toInteger()++);
}

DynamicVariable &DynamicVariable::operator--()
{
    assert(isType(ValueType::Integer));
    --toInteger();
    return *this;
}

DynamicVariable DynamicVariable::operator--(int)
{
    assert(isType(ValueType::Integer));
    return DynamicVariable(toInteger()--);
}

DynamicVariable &DynamicVariable::operator+=(const StringType &value)
{
    assert(isType(ValueType::String));
    toString() += value;
    return *this;
}

DynamicVariable &DynamicVariable::operator+=(const DynamicVariable &value)
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this += static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this += static_cast<FloatType>(value.toFloat());

        case ValueType::String:
            return *this += static_cast<StringType>(value.toString());

        default:
            break;
    }

    assert("Unsupported action");
    return *this;
}

DynamicVariable &DynamicVariable::operator-=(const DynamicVariable &value)
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this -= static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this -= static_cast<FloatType>(value.toFloat());

        default:
            break;
    }

    assert("Unsupported action");
    return *this;
}

DynamicVariable DynamicVariable::operator+(const StringType &value) const
{
    assert(isType(ValueType::String));
    return toString() + value;
}

DynamicVariable DynamicVariable::operator+(const DynamicVariable &value) const
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this + static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this + static_cast<FloatType>(value.toFloat());

        case ValueType::String:
            return *this + static_cast<StringType>(value.toString());

        default:
            break;
    }

    assert("Unsupported action");
    return *this;
}

DynamicVariable DynamicVariable::operator-(const DynamicVariable &value) const
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this - static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this - static_cast<FloatType>(value.toFloat());

        default:
            break;
    }

    assert("Unsupported action");
    return *this;
}

DynamicVariable &DynamicVariable::operator*=(const DynamicVariable &value)
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this *= static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this *= static_cast<FloatType>(value.toFloat());

        default:
            break;
    }

    assert("Unsupported action");
    return *this;
}

DynamicVariable DynamicVariable::operator*(const DynamicVariable &value) const
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this * static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this * static_cast<FloatType>(value.toFloat());

        default:
            break;
    }

    assert("Unsupported action");
    return *this;
}

DynamicVariable &DynamicVariable::operator/=(const DynamicVariable &value)
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this /= static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this /= static_cast<FloatType>(value.toFloat());

        default:
            break;
    }

    assert("Unsupported action");
    return *this;
}

DynamicVariable DynamicVariable::operator/(const DynamicVariable &value) const
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this / static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this / static_cast<FloatType>(value.toFloat());

        default:
            break;
    }

    assert("Unsupported action");
    return *this;
}

DynamicVariable &DynamicVariable::operator%=(const DynamicVariable &value)
{
    assert(value.isType(ValueType::Integer));
    return *this %= static_cast<IntType>(value.toInteger());
}

DynamicVariable DynamicVariable::operator%(const DynamicVariable &value) const
{
    assert(value.isType(ValueType::Integer));
    return *this % static_cast<IntType>(value.toInteger());
}

DynamicVariable::SizeType DynamicVariable::size() const
{
    if(isType(ValueType::Array))
    {
        return toArray().size();
    }

    return toString().size();
}

bool DynamicVariable::isEmpty() const
{
    if(isType(ValueType::Array))
    {
        return toArray().isEmpty();
    }

    return toString().isEmpty();
}


DynamicVariable DynamicVariable::operator[](DynamicVariable::SizeType pos)
{
    if(isType(ValueType::String))
    {
        return DynamicVariable(StringType(1, toString()[pos]));
    }

    return DynamicVariable(toArray()[pos]);
}

void DynamicVariable::push(const DynamicVariable &value) { toArray().push(value.m_value); }

DynamicVariable DynamicVariable::pop() { return toArray().pop(); }

void DynamicVariable::insert(const DynamicVariable &value, DynamicVariable::SizeType pos)
{
    toArray().insert(value.m_value, pos);
}

DynamicVariable DynamicVariable::removeAt(DynamicVariable::SizeType pos)
{
    return toArray().removeAt(pos);
}

void DynamicVariable::clear() { toArray().clear(); }

void DynamicVariable::append(const StringType &str) { toString().append(str); }

DynamicVariable DynamicVariable::subString(DynamicVariable::SizeType from,
                                           DynamicVariable::SizeType count)
{
    return toString().subString(from, count);
}
