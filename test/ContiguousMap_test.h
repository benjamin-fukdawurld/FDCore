#ifndef FDCORE_CONTIGUOUSMAP_TEST_H
#define FDCORE_CONTIGUOUSMAP_TEST_H

#include <FDCore/Common/ContiguousMap.h>
#include <gtest/gtest.h>
#include <string>

TEST(ContiguousMap_test, test_hashKey)
{
    FDCore::ContiguousMap<std::string, int> testMap;
    std::string key;

    ASSERT_EQ(testMap.hashKey(key), testMap.hash_function()(key));
}

TEST(ContiguousMap_test, test_empty)
{
    FDCore::ContiguousMap<std::string, int> testMap;
    ASSERT_TRUE(testMap.empty());

    testMap.insert("test", 0);
    ASSERT_FALSE(testMap.empty());
}

TEST(ContiguousMap_test, test_size)
{
    FDCore::ContiguousMap<std::string, int> testMap;
    ASSERT_EQ(testMap.size(), 0u);

    testMap.insert("1", 1);
    ASSERT_EQ(testMap.size(), 1);

    testMap.insert("2", 2);
    ASSERT_EQ(testMap.size(), 2);

    testMap.insert("3", 3);
    ASSERT_EQ(testMap.size(), 3);

    testMap.insert("4", 4);
    ASSERT_EQ(testMap.size(), 4);

    testMap.erase("4");
    ASSERT_EQ(testMap.size(), 3);

    testMap.erase("4");
    ASSERT_EQ(testMap.size(), 3);

    testMap.erase("3");
    ASSERT_EQ(testMap.size(), 2);
}

TEST(ContiguousMap_test, test_clear)
{
    FDCore::ContiguousMap<std::string, int> testMap;
    ASSERT_EQ(testMap.size(), 0u);

    testMap.insert("1", 1);
    testMap.insert("2", 2);
    testMap.insert("3", 3);
    testMap.insert("4", 4);

    ASSERT_EQ(testMap.size(), 4);
    testMap.clear();
    ASSERT_TRUE(testMap.empty());
}

TEST(ContiguousMap_test, test_contains)
{
    FDCore::ContiguousMap<std::string, int> testMap;
    ASSERT_EQ(testMap.size(), 0u);

    testMap.insert("1", 1);
    testMap.insert("2", 2);
    testMap.insert("3", 3);
    testMap.insert("4", 4);
    testMap.insert("5", 5);

    ASSERT_TRUE(testMap.contains("1"));
    ASSERT_TRUE(testMap.contains("2"));
    ASSERT_TRUE(testMap.contains("3"));
    ASSERT_TRUE(testMap.contains("4"));
    ASSERT_TRUE(testMap.contains("5"));
    testMap.clear();
    ASSERT_FALSE(testMap.contains("6"));
}

TEST(ContiguousMap_test, test_insert)
{
    FDCore::ContiguousMap<std::string, int> testMap;
    ASSERT_EQ(testMap.size(), 0u);

    std::string key = "1";
    int val = 1;
    testMap.insert(key, val);
    testMap.insert("2", 2);
    testMap.insert(std::make_pair("3", 3));
    testMap.emplace("4", 4);
    testMap.insert("5", 5);

    ASSERT_EQ(testMap.size(), 5u);

    auto second = testMap.begin();
    auto first = second++;
    while(second != testMap.end())
    {
        ASSERT_LT(testMap.hashKey(first->first), testMap.hashKey(second->first));
        first = second++;
    }
}

TEST(ContiguousMap_test, test_erase)
{
    FDCore::ContiguousMap<std::string, int> testMap;
    testMap.insert("1", 1);
    testMap.insert("2", 2);
    testMap.insert("3", 3);
    testMap.insert("4", 4);
    testMap.insert("5", 5);

    ASSERT_EQ(testMap.size(), 5u);
    ASSERT_FALSE(testMap.erase("6"));
    ASSERT_EQ(testMap.size(), 5u);
    ASSERT_TRUE(testMap.erase("1"));
    ASSERT_EQ(testMap.size(), 4u);

    testMap.erase(testMap.begin());
    ASSERT_EQ(testMap.size(), 3u);

    auto second = testMap.begin();
    auto first = second++;
    second++;
    testMap.erase(first, second);
    ASSERT_EQ(testMap.size(), 1u);
}

TEST(ContiguousMap_test, test_access)
{
    FDCore::ContiguousMap<std::string, std::string> testMap;
    const FDCore::ContiguousMap<std::string, std::string> &c_testMap(testMap);
    testMap.insert("1", "1");
    testMap.insert("2", "2");
    testMap.insert("3", "3");
    testMap.insert("4", "4");
    testMap.insert("5", "5");
    testMap.insert("5", "5.1");

    for(auto &[key, value]: testMap)
        std::cout << key << ": " << value << std::endl;

    ASSERT_EQ(testMap.size(), 6u);
    ASSERT_STREQ(testMap.at("1")->c_str(), "1");
    ASSERT_STREQ(c_testMap.at("2")->c_str(), "2");
    ASSERT_STREQ(c_testMap["3"]->c_str(), "3");
    ASSERT_STREQ(testMap["4"]->c_str(), "4");
    ASSERT_STREQ(testMap["5"]->c_str(), "5");
}

#endif // FDCORE_CONTIGUOUSMAP_TEST_H