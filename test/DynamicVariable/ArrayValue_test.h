#ifndef FDCORE_ARRAYVALUE_TEST_H
#define FDCORE_ARRAYVALUE_TEST_H

#include <FDCore/DynamicVariable/ArrayValue.h>
#include <FDCore/DynamicVariable/BoolValue.h>
#include <FDCore/DynamicVariable/FloatValue.h>
#include <FDCore/DynamicVariable/IntValue.h>
#include <FDCore/DynamicVariable/StringValue.h>
#include <gtest/gtest.h>
#include <iostream>

static const FDCore::ArrayValue::ArrayType TEST_ARRAY_VALUE = {
    FDCore::AbstractValue::Ptr(new FDCore::IntValue(42)),
    FDCore::AbstractValue::Ptr(new FDCore::BoolValue(true)),
    FDCore::AbstractValue::Ptr(new FDCore::FloatValue(3.14159)),
    FDCore::AbstractValue::Ptr(new FDCore::StringValue("text"))
};

TEST(ArrayValue_test, test_constructors)
{
    ASSERT_TRUE(FDCore::ArrayValue().isEmpty());
    ASSERT_EQ(FDCore::ArrayValue().size(), 0);
    ASSERT_FALSE(FDCore::ArrayValue(TEST_ARRAY_VALUE).isEmpty());
    ASSERT_EQ(FDCore::ArrayValue(TEST_ARRAY_VALUE).size(), TEST_ARRAY_VALUE.size());
    ASSERT_EQ(FDCore::ArrayValue({ FDCore::AbstractValue::Ptr(new FDCore::IntValue(42)),
                                   FDCore::AbstractValue::Ptr(new FDCore::BoolValue(true)),
                                   FDCore::AbstractValue::Ptr(new FDCore::FloatValue(3.14159)),
                                   FDCore::AbstractValue::Ptr(new FDCore::StringValue("text")) })
                .size(),
              TEST_ARRAY_VALUE.size());
}

TEST(ArrayValue_test, test_cast_operators)
{
    ASSERT_TRUE(static_cast<FDCore::ArrayValue::ArrayType>(FDCore::ArrayValue()).empty());
    ASSERT_FALSE(
      static_cast<const FDCore::ArrayValue::ArrayType &>(FDCore::ArrayValue(TEST_ARRAY_VALUE))
        .empty());

    FDCore::ArrayValue value(TEST_ARRAY_VALUE);
    const auto &arr = static_cast<const FDCore::ArrayValue::ArrayType &>(value);
    for(size_t i = 0; i < TEST_ARRAY_VALUE.size(); ++i)
    {
        ASSERT_EQ(value[i], arr[i]);
    }
}

TEST(ArrayValue_test, test_member_functions)
{
    FDCore::ArrayValue value(TEST_ARRAY_VALUE);
    FDCore::ArrayValue::ArrayType arr(TEST_ARRAY_VALUE);
    FDCore::AbstractValue::Ptr cell(new FDCore::IntValue(42));
    arr.push_back(cell);
    value.push(cell);
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


#endif // FDCORE_ARRAYVALUE_TEST_H
