#ifndef FDCORE_STRINGVALUE_TEST_H
#define FDCORE_STRINGVALUE_TEST_H

#include <FDCore/DynamicVariable/StringValue.h>
#include <gtest/gtest.h>
#include <iostream>

static const FDCore::StringValue::StringType TEST_STRING_VALUE("text");

TEST(StringValue_test, test_constructors)
{
    ASSERT_EQ(FDCore::StringValue(), FDCore::StringValue::StringType());
    ASSERT_EQ(FDCore::StringValue(TEST_STRING_VALUE), TEST_STRING_VALUE);
    FDCore::StringValue value;
    value = TEST_STRING_VALUE;
    ASSERT_EQ(value, TEST_STRING_VALUE);
}

TEST(StringValue_test, test_comparison_operators)
{
    ASSERT_TRUE(FDCore::StringValue(TEST_STRING_VALUE) == TEST_STRING_VALUE);
    ASSERT_TRUE(TEST_STRING_VALUE == FDCore::StringValue(TEST_STRING_VALUE));
    ASSERT_TRUE(FDCore::StringValue(TEST_STRING_VALUE) != FDCore::StringValue::StringType());
}

TEST(StringValue_test, test_concat_operators)
{
    FDCore::StringValue::StringType test;
    FDCore::StringValue value;
    ASSERT_EQ(value += TEST_STRING_VALUE, test += TEST_STRING_VALUE);
    ASSERT_EQ(value + TEST_STRING_VALUE, test + TEST_STRING_VALUE);
}

TEST(StringValue_test, test_stream_operators)
{
    FDCore::StringValue::StringType test = TEST_STRING_VALUE;
    FDCore::StringValue value;
    std::stringstream ss;
    ss << test;
    ss >> value;
    ASSERT_EQ(value, test);
    ss.clear();
    value = "result";
    ss << value;
    ss >> test;
    ASSERT_EQ(value, test);
}

TEST(StringValue_test, test_member_functions)
{
    FDCore::StringValue::StringType test = TEST_STRING_VALUE;
    FDCore::StringValue value;
    ASSERT_TRUE(value.isEmpty());
    ASSERT_FALSE(FDCore::StringValue(TEST_STRING_VALUE).isEmpty());
    ASSERT_EQ(FDCore::StringValue(TEST_STRING_VALUE).size(), test.size());
    value = TEST_STRING_VALUE;
    ASSERT_FALSE(value.isEmpty());
    value.clear();
    ASSERT_TRUE(value.isEmpty());
    value = test;
    ASSERT_EQ(value[0], test[0]);
    value.append(" string");
    test.append(" string");
    ASSERT_EQ(value, test);
    ASSERT_EQ(value.subString(0, 4), test.substr(0, 4));
}


#endif // FDCORE_STRINGVALUE_TEST_H
