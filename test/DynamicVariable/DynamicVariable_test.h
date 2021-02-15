#ifndef FDCORE_DYNAMICVARIABLE_TEST_H
#define FDCORE_DYNAMICVARIABLE_TEST_H

#include <iostream>
#include <sstream>

#include "ArrayValue_test.h"
#include "BoolValue_test.h"
#include "FloatValue_test.h"
#include "IntValue_test.h"
#include "StringValue_test.h"

#include <FDCore/DynamicVariable/DynamicVariable.h>

static constexpr FDCore::DynamicVariable::IntType TEST_DYN_INT_VALUE = 10;
static constexpr FDCore::DynamicVariable::FloatType TEST_DYN_FLOAT_VALUE = 3.14159F;
static const FDCore::DynamicVariable::StringType TEST_DYN_STRING_VALUE("text");
static const FDCore::ArrayValue::ArrayType TEST_DYN_ARRAY_VALUE = {
    FDCore::AbstractValue::Ptr(new FDCore::IntValue(42)),
    FDCore::AbstractValue::Ptr(new FDCore::BoolValue(true)),
    FDCore::AbstractValue::Ptr(new FDCore::FloatValue(3.14159)),
    FDCore::AbstractValue::Ptr(new FDCore::StringValue("text"))
};

TEST(DynamicVariable_test, test_constructors)
{
    using namespace FDCore;

    ASSERT_EQ(FDCore::DynamicVariable().getValueType(), FDCore::ValueType::None);

    ASSERT_EQ(FDCore::DynamicVariable(true), true);
    ASSERT_EQ(FDCore::DynamicVariable(false), false);

    ASSERT_EQ(FDCore::DynamicVariable(TEST_DYN_INT_VALUE), TEST_DYN_INT_VALUE);
    ASSERT_EQ(FDCore::DynamicVariable(2U), 2U);

    ASSERT_FLOAT_EQ(static_cast<FDCore::DynamicVariable::FloatType>(
                      FDCore::DynamicVariable(TEST_DYN_FLOAT_VALUE)),
                    TEST_DYN_FLOAT_VALUE);
    ASSERT_FLOAT_EQ(
      static_cast<FDCore::DynamicVariable::FloatType>(FDCore::DynamicVariable(1.61803)), 1.61803);

    ASSERT_EQ(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE), TEST_DYN_STRING_VALUE);
    ASSERT_EQ(FDCore::DynamicVariable("test"), DynamicVariable::StringViewType("test"));

    ASSERT_EQ(-42_var, -42);
    ASSERT_FLOAT_EQ(static_cast<FDCore::DynamicVariable::FloatType>(1.61803_var), 1.61803);
    ASSERT_EQ("test"_var, FDCore::DynamicVariable::StringType("test"));

    FDCore::DynamicVariable value;
    value = TEST_DYN_INT_VALUE;
    ASSERT_EQ(value, TEST_DYN_INT_VALUE);
    ASSERT_NE(value, 2);
    value = TEST_DYN_FLOAT_VALUE;
    ASSERT_EQ(value, TEST_DYN_FLOAT_VALUE);
    ASSERT_NE(value, 2.0F);
    value = TEST_DYN_STRING_VALUE;
    ASSERT_EQ(value, TEST_DYN_STRING_VALUE);
    ASSERT_NE(value, "not the same string");
}

TEST(DynamicVariable_test, test_comparison_operators)
{
    ASSERT_TRUE(FDCore::DynamicVariable() == nullptr);
    ASSERT_TRUE(FDCore::DynamicVariable() == FDCore::DynamicVariable());

    ASSERT_TRUE(FDCore::DynamicVariable(true) == true);
    ASSERT_TRUE(FDCore::DynamicVariable(true) == FDCore::DynamicVariable(true));
    ASSERT_TRUE(FDCore::DynamicVariable(true) != false);
    ASSERT_TRUE(FDCore::DynamicVariable(true) != FDCore::DynamicVariable(false));

    ASSERT_TRUE(FDCore::DynamicVariable(0) == 0);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_INT_VALUE) ==
                FDCore::DynamicVariable(TEST_DYN_INT_VALUE));
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_INT_VALUE) == TEST_DYN_INT_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_INT_VALUE) != -TEST_DYN_INT_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_INT_VALUE) <= TEST_DYN_INT_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_INT_VALUE) < 2 * TEST_DYN_INT_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_INT_VALUE) >= TEST_DYN_INT_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_INT_VALUE) > 0);

    ASSERT_TRUE(FDCore::DynamicVariable(0.0F) == 0.0F);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_FLOAT_VALUE) ==
                FDCore::DynamicVariable(TEST_DYN_FLOAT_VALUE));
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_FLOAT_VALUE) == TEST_DYN_FLOAT_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_FLOAT_VALUE) != -TEST_DYN_FLOAT_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_FLOAT_VALUE) <= TEST_DYN_FLOAT_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_FLOAT_VALUE) < 2.0F * TEST_DYN_FLOAT_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_FLOAT_VALUE) >= TEST_DYN_FLOAT_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_FLOAT_VALUE) > 0.0F);

    ASSERT_TRUE(FDCore::DynamicVariable(FDCore::DynamicVariable::StringType("")) ==
                FDCore::DynamicVariable::StringType(""));
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE) ==
                FDCore::DynamicVariable(TEST_DYN_STRING_VALUE));
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE) == TEST_DYN_STRING_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE) !=
                FDCore::DynamicVariable::StringType("some other string"));
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE) !=
                FDCore::DynamicVariable(FDCore::DynamicVariable::StringType("some other string")));

    ASSERT_FALSE(FDCore::DynamicVariable(FDCore::DynamicVariable::StringType("")) ==
                 FDCore::DynamicVariable(false));
    ASSERT_TRUE(FDCore::DynamicVariable(FDCore::DynamicVariable::StringType("")) !=
                FDCore::DynamicVariable(false));
    ASSERT_FALSE(FDCore::DynamicVariable(FDCore::DynamicVariable::StringType("")) ==
                 FDCore::DynamicVariable(1));
    ASSERT_TRUE(FDCore::DynamicVariable(FDCore::DynamicVariable::StringType("")) !=
                FDCore::DynamicVariable(1));
    ASSERT_FALSE(FDCore::DynamicVariable(FDCore::DynamicVariable::StringType("")) ==
                 FDCore::DynamicVariable(1.0F));
    ASSERT_TRUE(FDCore::DynamicVariable(FDCore::DynamicVariable::StringType("")) !=
                FDCore::DynamicVariable(1.0F));
}

TEST(DynamicVariable_test, test_int_operators)
{
    {
        int test = 1;
        FDCore::DynamicVariable value(1);
        ASSERT_EQ(value += 0, test += 0);
        ASSERT_EQ(value + 0, test + 0);
        ASSERT_EQ(value += 1, test += 1);
        ASSERT_EQ(value += value, test += test);
        ASSERT_EQ(value + value, test + test);

        ASSERT_EQ(value + test, test + value);
        ASSERT_EQ(value += test, 8);
        ASSERT_EQ(test += value, 12);

        value = test = -1;
        ASSERT_EQ(+value, +test);
        value = test = 0;
        ASSERT_EQ(value++, test++);
        ASSERT_EQ(++value, ++test);
    }

    {
        int test = 4;
        FDCore::DynamicVariable value(4);
        ASSERT_EQ(value -= 0, test -= 0);
        ASSERT_EQ(value - 0, test - 0);
        ASSERT_EQ(value -= 1, test -= 1);
        ASSERT_EQ(value -= value, test -= test);

        value = test = 2;
        ASSERT_EQ(value - value, test - test);
        ASSERT_EQ(value - test, test - value);
        ASSERT_EQ(value -= test, 0);
        value = 4LU;
        ASSERT_EQ(test -= value, -2);

        value = test = -1;
        ASSERT_EQ(-value, -test);
        value = test = 0;
        ASSERT_EQ(-value, 0);
        ASSERT_EQ(value--, test--);
        ASSERT_EQ(value--, test--);
    }

    {
        int test = 1;
        FDCore::DynamicVariable value(1);
        ASSERT_EQ(FDCore::DynamicVariable(value) *= 0, 0);
        ASSERT_EQ(value * 0, 0);
        ASSERT_EQ(FDCore::DynamicVariable(value) *= 1, value);
        ASSERT_EQ(value * 1, value);
        ASSERT_EQ(FDCore::DynamicVariable(value) *= -1, -value);
        ASSERT_EQ(value *= 2, test *= 2);
        ASSERT_EQ(value * 2, test * 2);
        ASSERT_EQ(value *= value, test *= test);
        ASSERT_EQ(value * value, test * test);
    }

    {
        int test = TEST_DYN_INT_VALUE;
        FDCore::DynamicVariable value(TEST_DYN_INT_VALUE);
        ASSERT_EQ(FDCore::DynamicVariable(value) /= 1, value);
        ASSERT_EQ(value / 1, value);
        ASSERT_EQ(FDCore::DynamicVariable(value) /= -1, -value);
        ASSERT_EQ(value /= 2, test /= 2);
        ASSERT_EQ(value / 2, test / 2);
        ASSERT_EQ(value / value, test / test);
        ASSERT_EQ(100 / value, 100 / test);
        value = 2;
        test = 4;
        ASSERT_EQ(test /= value, 2);
    }

    {
        int test = TEST_DYN_INT_VALUE;
        FDCore::DynamicVariable value(3);
        ASSERT_EQ(FDCore::DynamicVariable(test) % value, 1);
        ASSERT_EQ(FDCore::DynamicVariable(test) %= value, 1);
        ASSERT_EQ(test % value, 1);
        ASSERT_EQ(test %= value, 1);
    }

    {
        int test = 0;
        FDCore::DynamicVariable value(0);
        ASSERT_EQ(~value, ~test);
        ASSERT_EQ(value | 1, test | 1);
        ASSERT_EQ(value |= 1, test |= 1);
        ASSERT_EQ(value << 1, test << 1);
        ASSERT_EQ(value <<= 2, test <<= 2);
        ASSERT_EQ(value >> 1, test >> 1);
        ASSERT_EQ(value >>= 2, test >>= 2);

        value = test = ~0;
        ASSERT_EQ(value & 0x8, test & 0x8);
        ASSERT_EQ(value &= 0x8, test &= 0x8);
        value = 1;
        ASSERT_EQ(test & value, 0x8 & 1);
        ASSERT_EQ(test | value, 0x8 | 1);
        ASSERT_EQ(test |= value, 0x8 | 1);
        ASSERT_EQ(test &= value, 0x9 & 1);


        value = test = 0b11011;
        ASSERT_EQ(value ^ 2, test ^ 2);
        ASSERT_EQ(value ^= 2, test ^= 2);
        ASSERT_EQ(0xFF ^ value, 0xFF ^ test);
    }

    {
        int test = TEST_DYN_INT_VALUE;
        FDCore::DynamicVariable value(FDCore::ValueType::Integer);
        std::stringstream ss;
        ss << test;
        ss >> value;
        ASSERT_EQ(value, test);
        ss.clear();
        value = 0;
        ss << value;
        ss >> test;
        ASSERT_EQ(value, test);
    }
}

TEST(DynamicVariable_test, test_float_operators)
{
    {
        float test = 1;
        FDCore::DynamicVariable value(1.0F);
        ASSERT_FLOAT_EQ(static_cast<float>(value += 0), test += 0);
        ASSERT_FLOAT_EQ(static_cast<float>(value + 0.0), test + 0.0);
        ASSERT_FLOAT_EQ(static_cast<float>(value += 1), test += 1);
        ASSERT_FLOAT_EQ(static_cast<float>(value += value), test += test);
        ASSERT_FLOAT_EQ(static_cast<float>(value + value), test + test);

        ASSERT_FLOAT_EQ(static_cast<float>(value + test), test + value);
        ASSERT_FLOAT_EQ(static_cast<float>(value += test), 8u);
        ASSERT_FLOAT_EQ(test += value, 12.0);

        value = test = -1.0F;
        ASSERT_FLOAT_EQ(static_cast<float>(+value), +test);
    }

    {
        float test = 4.0F;
        FDCore::DynamicVariable value(4.0F);
        ASSERT_FLOAT_EQ(static_cast<float>(value -= 0), test -= 0);
        ASSERT_FLOAT_EQ(static_cast<float>(value - 0), test - 0);
        ASSERT_FLOAT_EQ(static_cast<float>(value -= 1), test -= 1);
        ASSERT_FLOAT_EQ(static_cast<float>(value -= value), test -= test);

        value = test = 2.0F;
        ASSERT_FLOAT_EQ(static_cast<float>(value - value), test - test);
        ASSERT_FLOAT_EQ(static_cast<float>(value - test), test - value);
        ASSERT_FLOAT_EQ(static_cast<float>(value -= test), 0.0F);
        value = 4.0F;
        ASSERT_FLOAT_EQ(test -= value, -2.0F);

        value = test = -1.0f;
        ASSERT_FLOAT_EQ(static_cast<float>(-value), -test);
        value = test = 0.0f;
        ASSERT_FLOAT_EQ(static_cast<float>(-value), 0);
    }

    {
        float test = 1;
        FDCore::DynamicVariable value(1.0F);
        ASSERT_FLOAT_EQ(static_cast<float>(FDCore::DynamicVariable(value) *= 0), 0);
        ASSERT_FLOAT_EQ(static_cast<float>(value * 0), 0);
        ASSERT_FLOAT_EQ(static_cast<float>(FDCore::DynamicVariable(value) *= 1),
                        static_cast<float>(value));
        ASSERT_FLOAT_EQ(static_cast<float>(value * 1), static_cast<float>(value));
        ASSERT_FLOAT_EQ(static_cast<float>(FDCore::DynamicVariable(value) *= -1),
                        static_cast<float>(-value));
        ASSERT_FLOAT_EQ(static_cast<float>(value *= 2), test *= 2);
        ASSERT_FLOAT_EQ(static_cast<float>(value * 2), test * 2);
        ASSERT_FLOAT_EQ(static_cast<float>(value *= value), test *= test);
        ASSERT_FLOAT_EQ(static_cast<float>(value * value), test * test);
    }

    {
        float test = TEST_DYN_FLOAT_VALUE;
        FDCore::DynamicVariable value(TEST_DYN_FLOAT_VALUE);
        ASSERT_FLOAT_EQ(static_cast<float>(FDCore::DynamicVariable(value) /= 1),
                        static_cast<float>(value));
        ASSERT_FLOAT_EQ(static_cast<float>(value / 1), static_cast<float>(value));
        ASSERT_FLOAT_EQ(static_cast<float>(FDCore::DynamicVariable(value) /= -1),
                        static_cast<float>(-value));
        ASSERT_FLOAT_EQ(static_cast<float>(value /= 2), test /= 2);
        ASSERT_FLOAT_EQ(static_cast<float>(value / 2), test / 2);
        ASSERT_FLOAT_EQ(static_cast<float>(value / value), test / test);
        ASSERT_FLOAT_EQ(static_cast<float>(100.0F / value), 100 / test);
        value = 2.0F;
        test = 4.0F;
        ASSERT_FLOAT_EQ(test /= value, 2);
    }

    {
        float test = TEST_DYN_FLOAT_VALUE;
        FDCore::DynamicVariable value(FDCore::ValueType::Float);
        std::stringstream ss;
        ss << test;
        ss >> value;
        ASSERT_FLOAT_EQ(static_cast<float>(value), test);
        ss.clear();
        value = 0.0F;
        ss << value;
        ss >> test;
        ASSERT_FLOAT_EQ(static_cast<float>(value), test);
    }
}

TEST(DynamicVariable_test, test_bool_operators)
{
    {
        FDCore::DynamicVariable b;
        FDCore::DynamicVariable other(true);
        b = true;
        ASSERT_FALSE(!b);

        ASSERT_TRUE(b == true);
        ASSERT_TRUE(b == other);

        ASSERT_TRUE(b != false);
        ASSERT_TRUE(b != !other);

        ASSERT_FALSE(b && false);
        ASSERT_TRUE(b && other);

        ASSERT_TRUE(b || false);
        ASSERT_TRUE(b || other);

        ASSERT_TRUE(b ^ false);
        ASSERT_FALSE(b ^ other);
    }

    {
        FDCore::DynamicVariable b(FDCore::ValueType::Boolean);
        bool tmp = true;
        std::stringstream ss;
        ss << tmp;
        ss >> b;
        ASSERT_TRUE(b);
        tmp = false;
        ss.clear();
        ss << b;
        ss >> tmp;
        ASSERT_TRUE(tmp);
    }
}

TEST(DynamicVariable_test, test_string_operators)
{
    {
        FDCore::DynamicVariable::StringType test;
        FDCore::DynamicVariable value(FDCore::DynamicVariable::StringType(""));
        ASSERT_EQ(value += TEST_DYN_STRING_VALUE, test += TEST_DYN_STRING_VALUE);
        ASSERT_EQ(value + TEST_DYN_STRING_VALUE, test + TEST_DYN_STRING_VALUE);
    }

    {
        FDCore::DynamicVariable::StringType test = TEST_DYN_STRING_VALUE;
        FDCore::DynamicVariable value(FDCore::DynamicVariable::StringType(""));
        std::stringstream ss;
        ss << test;
        ss >> value;
        std::cout << value << std::endl;
        ASSERT_EQ(value, test);
        ss.clear();
        value = FDCore::DynamicVariable::StringType("result");
        ss << value;
        ss >> test;
        ASSERT_EQ(value, test);
    }

    {
        FDCore::DynamicVariable::StringType test = TEST_DYN_STRING_VALUE;
        FDCore::DynamicVariable value(FDCore::DynamicVariable::StringType(""));
        ASSERT_TRUE(value.isEmpty());
        ASSERT_FALSE(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE).isEmpty());
        ASSERT_EQ(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE).size(), test.size());
        value = TEST_DYN_STRING_VALUE;
        ASSERT_FALSE(value.isEmpty());
        value.clear();
        ASSERT_TRUE(value.isEmpty());
        value = test;
        ASSERT_EQ(value[0], FDCore::DynamicVariable::StringType(1, test[0]));
        value.append(" string");
        test.append(" string");
        ASSERT_EQ(value, test);
        ASSERT_EQ(value.subString(0, 4), test.substr(0, 4));
    }
}

TEST(DynamicVariable_test, test_array_operators)
{
    {
        ASSERT_TRUE(static_cast<FDCore::DynamicVariable::ArrayType>(
                      FDCore::DynamicVariable(FDCore::ValueType::Array))
                      .empty());
        ASSERT_FALSE(static_cast<const FDCore::DynamicVariable::ArrayType &>(
                       FDCore::DynamicVariable(TEST_ARRAY_VALUE))
                       .empty());

        FDCore::DynamicVariable value(TEST_ARRAY_VALUE);
        const auto &arr = static_cast<const FDCore::DynamicVariable::ArrayType &>(value);
        for(size_t i = 0; i < TEST_ARRAY_VALUE.size(); ++i)
        {
            ASSERT_EQ(value[i], arr[i]);
        }
    }

    {
        FDCore::DynamicVariable value(TEST_ARRAY_VALUE);
        FDCore::DynamicVariable::ArrayType arr(TEST_ARRAY_VALUE);
        FDCore::AbstractValue::Ptr cell(new FDCore::IntValue(42));
        arr.push_back(cell);
        value.push(FDCore::DynamicVariable(cell));
        ASSERT_EQ(value.size(), arr.size());
        ASSERT_EQ(value[value.size() - 1], arr.back());

        auto tmp = value.pop();
        ASSERT_EQ(tmp, cell);
        arr.pop_back();

        auto it = arr.begin();
        std::advance(it, 1);
        cell = *it;
        arr.erase(it);
        ASSERT_EQ(value.removeAt(1), cell);
        value.clear();
        ASSERT_TRUE(value.isEmpty());
    }
}

#endif // FDCORE_DYNAMICVARIABLE_TEST_H
