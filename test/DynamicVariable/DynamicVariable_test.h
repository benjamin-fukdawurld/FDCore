#ifndef FDCORE_DYNAMICVARIABLE_TEST_H
#define FDCORE_DYNAMICVARIABLE_TEST_H

#include "ArrayValue_test.h"
#include "BoolValue_test.h"
#include "FloatValue_test.h"
#include "IntValue_test.h"
#include "StringValue_test.h"

#include <FDCore/DynamicVariable/DynamicVariable.h>

static constexpr FDCore::DynamicVariable::IntType TEST_DYN_INT_VALUE = 10;
static constexpr FDCore::DynamicVariable::FloatType TEST_DYN_FLOAT_VALUE = 3.14159F;
static const FDCore::DynamicVariable::StringType TEST_DYN_STRING_VALUE("text");

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
    ASSERT_EQ(FDCore::DynamicVariable("test"), "test");

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
    value = TEST_STRING_VALUE;
    ASSERT_EQ(value, TEST_STRING_VALUE);
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

    ASSERT_TRUE(FDCore::DynamicVariable("") == "");
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE) ==
                FDCore::DynamicVariable(TEST_DYN_STRING_VALUE));
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE) == TEST_DYN_STRING_VALUE);
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE) != "some other string");
    ASSERT_TRUE(FDCore::DynamicVariable(TEST_DYN_STRING_VALUE) !=
                FDCore::DynamicVariable("some other string"));

    ASSERT_FALSE(FDCore::DynamicVariable("") == FDCore::DynamicVariable(false));
    ASSERT_TRUE(FDCore::DynamicVariable("") != FDCore::DynamicVariable(false));
    ASSERT_FALSE(FDCore::DynamicVariable("") == FDCore::DynamicVariable(1));
    ASSERT_TRUE(FDCore::DynamicVariable("") != FDCore::DynamicVariable(1));
    ASSERT_FALSE(FDCore::DynamicVariable("") == FDCore::DynamicVariable(1.0F));
    ASSERT_TRUE(FDCore::DynamicVariable("") != FDCore::DynamicVariable(1.0F));
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
        FDCore::DynamicVariable value;
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

#endif // FDCORE_DYNAMICVARIABLE_TEST_H
