#ifndef FDCORE_BOOLVALUE_TEST_H
#define FDCORE_BOOLVALUE_TEST_H

#include <FDCore/DynamicVariable/BoolValue.h>
#include <gtest/gtest.h>
#include <sstream>

TEST(BoolValue_test, test_constructors)
{
    ASSERT_FALSE(static_cast<bool>(FDCore::BoolValue()));
    ASSERT_TRUE(static_cast<bool>(FDCore::BoolValue(true)));

    FDCore::BoolValue b;
    b = true;
    ASSERT_TRUE(static_cast<bool>(b));
}

TEST(BoolValue_test, test_operators)
{
    FDCore::BoolValue b;
    FDCore::BoolValue other(true);
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

TEST(BoolValue_test, test_stream_operators)
{
    FDCore::BoolValue b;
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

#endif // FDCORE_BOOLVALUE_TEST_H
