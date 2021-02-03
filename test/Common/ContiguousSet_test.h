#ifndef FDCORE_CONTIGUOUSSET_TEST_H
#define FDCORE_CONTIGUOUSSET_TEST_H

#include <FDCore/Common/ContiguousSet.h>
#include <gtest/gtest.h>
#include <string>

TEST(ContiguousSet_test, test_hashKey)
{
    FDCore::ContiguousSet<std::string> testSet;
    std::string key;

    ASSERT_EQ(testSet.hashItem(key), testSet.hash_function()(key));
}

TEST(ContiguousSet_test, test_empty)
{
    FDCore::ContiguousSet<std::string> testSet;
    ASSERT_TRUE(testSet.empty());

    testSet.insert("test");
    ASSERT_FALSE(testSet.empty());
}

TEST(ContiguousSet_test, test_size)
{
    FDCore::ContiguousSet<std::string> testSet;
    ASSERT_EQ(testSet.size(), 0u);

    testSet.insert("1");
    ASSERT_EQ(testSet.size(), 1u);

    testSet.insert("2");
    ASSERT_EQ(testSet.size(), 2u);

    testSet.insert("3");
    ASSERT_EQ(testSet.size(), 3u);

    testSet.insert("4");
    ASSERT_EQ(testSet.size(), 4u);

    testSet.erase("4");
    ASSERT_EQ(testSet.size(), 3u);

    testSet.erase("4");
    ASSERT_EQ(testSet.size(), 3u);

    testSet.erase("3");
    ASSERT_EQ(testSet.size(), 2u);
}

TEST(ContiguousSet_test, test_clear)
{
    FDCore::ContiguousSet<std::string> testSet;
    ASSERT_EQ(testSet.size(), 0u);

    testSet.insert("1");
    testSet.insert("2");
    testSet.insert("3");
    testSet.insert("4");

    ASSERT_EQ(testSet.size(), 4u);
    testSet.clear();
    ASSERT_TRUE(testSet.empty());
}

TEST(ContiguousSet_test, test_contains)
{
    FDCore::ContiguousSet<std::string> testSet;
    ASSERT_EQ(testSet.size(), 0u);

    testSet.insert("1");
    testSet.insert("2");
    testSet.insert("3");
    testSet.insert("4");
    testSet.insert("5");

    ASSERT_TRUE(testSet.contains("1"));
    ASSERT_TRUE(testSet.contains("2"));
    ASSERT_TRUE(testSet.contains("3"));
    ASSERT_TRUE(testSet.contains("4"));
    ASSERT_TRUE(testSet.contains("5"));
    testSet.clear();
    ASSERT_FALSE(testSet.contains("6"));
}

TEST(ContiguousSet_test, test_insert)
{
    FDCore::ContiguousSet<std::string> testSet;
    ASSERT_EQ(testSet.size(), 0u);

    std::string key = "1";
    testSet.insert(key);
    testSet.insert("2");
    testSet.insert("3");
    testSet.emplace("4");
    testSet.insert("5");

    ASSERT_EQ(testSet.size(), 5u);

    auto second = testSet.begin();
    auto first = second++;
    while(second != testSet.end())
    {
        ASSERT_LT(testSet.hashItem(*first), testSet.hashItem(*second));
        first = second++;
    }
}

TEST(ContiguousSet_test, test_erase)
{
    FDCore::ContiguousSet<std::string> testSet;
    testSet.insert("1");
    testSet.insert("2");
    testSet.insert("3");
    testSet.insert("4");
    testSet.insert("5");

    ASSERT_EQ(testSet.size(), 5u);
    ASSERT_FALSE(testSet.erase("6"));
    ASSERT_EQ(testSet.size(), 5u);
    ASSERT_TRUE(testSet.erase("1"));
    ASSERT_EQ(testSet.size(), 4u);

    testSet.erase(testSet.begin());
    ASSERT_EQ(testSet.size(), 3u);

    auto second = testSet.begin();
    auto first = second++;
    second++;
    testSet.erase(first, second);
    ASSERT_EQ(testSet.size(), 1u);
}

TEST(ContiguousSet_test, test_access)
{
    FDCore::ContiguousSet<int> testSet;
    testSet.insert(1);
    testSet.insert(2);
    testSet.insert(3);
    testSet.insert(4);
    testSet.insert(5);

    ASSERT_EQ(testSet.size(), 5u);

    int i = 1;
    for(auto &it: testSet)
        ASSERT_EQ(it, i++);
}

#endif // FDCORE_CONTIGUOUSSET_TEST_H