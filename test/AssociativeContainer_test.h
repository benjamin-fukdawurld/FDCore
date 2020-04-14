#ifndef ASSOCIATIVECONTAINER_TEST_H
#define ASSOCIATIVECONTAINER_TEST_H

#include <gtest/gtest.h>

#include <string>

#ifndef DEBUG
#define DEBUG
#define NEED_UNDEF
#endif

#include <FDCore/AssociativeContainer.h>


class FDCore_AssociativeContainer_int_str : public ::testing::Test
{
    protected:
        typedef const FDCore::AssociativeContainer<int, std::string>::cell_type const_cell_type;
        FDCore::AssociativeContainer<int, std::string> container;

    public:
        ~FDCore_AssociativeContainer_int_str() override = default;

        void SetUp() override;

        const FDCore::AssociativeContainer<int, std::string> &getContainer() const
        {
            return container;
        }

        void printContainer() const
        {
            for(auto &[key, value]: container)
            {
                std::cerr << key.key << ": " << value << std::endl;
            }
        }
};

void FDCore_AssociativeContainer_int_str::SetUp()
{
    container.insert(0, "0");
    container.insert(1, "1.2");
    container.insert(1, "1");
    container.insert(2, "2");
    container.insert(3, "3");
    container.insert(4, "4");
    container.insert(5, "5");
    container.insert(6, "6");
    container.insert(7, "7");
    container.insert(8, "8");
    container.insert(9, "9");
    container.insert(10, "10");
}

TEST_F(FDCore_AssociativeContainer_int_str, HashKeyTest)
{
    std::hash<int> h;
    ASSERT_EQ(container.hashKey(11), h(11));
}

TEST_F(FDCore_AssociativeContainer_int_str, FindTest)
{
    ASSERT_EQ(container.find(11), container.end());
    auto it = container.find(1);
    ASSERT_NE(it, container.end());
    ASSERT_EQ(it->value, "1");
    ASSERT_EQ(it->key.key, 1);

    ASSERT_EQ(getContainer().find(12), container.cend());
    auto cit = getContainer().find(2);
    ASSERT_NE(cit, container.end());
    ASSERT_EQ(cit->value, "2");

}

TEST_F(FDCore_AssociativeContainer_int_str, FindLastTest)
{
    ASSERT_EQ(container.find_last(11), container.end());
    auto it = container.find_last(1);
    ASSERT_NE(it, container.end());

    ASSERT_EQ(it->value, "1.2");
    ASSERT_EQ(it->key.key, 1);

    ASSERT_EQ(getContainer().find_last(12), container.cend());
    auto cit = getContainer().find_last(1);
    ASSERT_NE(cit, container.end());
    ASSERT_EQ(cit->value, "1.2");
}

TEST_F(FDCore_AssociativeContainer_int_str, FindIfTest)
{
    ASSERT_EQ(container.find_if([](const_cell_type &cell)
    {
        return cell.value == "11";
    }), container.end());
    auto it = container.find_if([](const_cell_type &cell)
    {
        return cell.value == "3";
    });
    ASSERT_NE(it, container.end());
    ASSERT_EQ(it->value, "3");
    ASSERT_EQ(it->key.key, 3);

    ASSERT_EQ(getContainer().find_if([](const_cell_type &cell)
    {
        return cell.value == "12";
    }), container.cend());
    auto cit = getContainer().find_if([](const_cell_type &cell)
    {
        return cell.value == "4";
    });
    ASSERT_NE(cit, container.end());
    ASSERT_EQ(cit->value, "4");
    ASSERT_EQ(cit->key.key, 4);
}

TEST_F(FDCore_AssociativeContainer_int_str, FindLastIfTest)
{
    ASSERT_EQ(container.find_last_if([](const_cell_type &cell)
    {
        return cell.value == "11";
    }), container.end());

    auto it = container.find_last_if([](const_cell_type &cell)
    {
        return cell.value == "1.2";
    });
    ASSERT_NE(it, container.end());
    ASSERT_EQ(it->value, "1.2");
    ASSERT_EQ(it->key.key, 1);

    ASSERT_EQ(getContainer().find_last_if([](const_cell_type &cell)
    {
        return cell.value == "12";
    }), container.cend());
    auto cit = getContainer().find_last_if([](const_cell_type &cell)
    {
        return cell.value == "4";
    });
    ASSERT_NE(cit, container.end());
    ASSERT_EQ(cit->value, "4");
    ASSERT_EQ(cit->key.key, 4);
}

TEST_F(FDCore_AssociativeContainer_int_str, FindAllTest)
{
    {
        ASSERT_TRUE(container.find_all(11).empty());
        auto v = container.find_all(1);
        ASSERT_FALSE(v.empty());
        ASSERT_EQ(v.size(), 2u);
        ASSERT_EQ(v[0]->key.key, 1);
        ASSERT_EQ(v[1]->key.key, 1);
    }

    {
        ASSERT_TRUE(container.find_all_if([](const_cell_type &cell)
        {
            return cell.value.size() == 4;
        }).empty());
        auto v = container.find_all_if([](const_cell_type &cell)
        {
            return cell.value.size() == 1;
        });
        ASSERT_FALSE(v.empty());
        ASSERT_EQ(v.size(), container.size() - 2u);
    };

    {
        ASSERT_TRUE(getContainer().find_all(11).empty());
        auto v = getContainer().find_all(1);
        ASSERT_FALSE(v.empty());
        ASSERT_EQ(v.size(), 2u);
        ASSERT_EQ(v[0]->key.key, 1);
        ASSERT_EQ(v[1]->key.key, 1);
    }

    {
        ASSERT_TRUE(getContainer().find_all_if([](const_cell_type &cell)
        {
            return cell.value.size() == 4;
        }).empty());
        auto v = getContainer().find_all_if([](const_cell_type &cell)
        {
            return cell.value.size() == 1;
        });
        ASSERT_FALSE(v.empty());
        ASSERT_EQ(v.size(), getContainer().size() - 2u);
    };
}

TEST_F(FDCore_AssociativeContainer_int_str, ContainsTest)
{
    ASSERT_FALSE(container.contains(-1));
    ASSERT_TRUE(container.contains(1));
}

TEST_F(FDCore_AssociativeContainer_int_str, EmptyTest)
{
    ASSERT_FALSE(container.empty());
    FDCore::AssociativeContainer<int, std::string> tmp;
    ASSERT_TRUE(tmp.empty());
}

TEST_F(FDCore_AssociativeContainer_int_str, InsertTest)
{
    size_t s = container.size();
    container.insert(11, "11");
    ASSERT_EQ(container.size(), s + 1u);
    auto it = container.find(11);
    ASSERT_NE(it, container.end());
    ASSERT_EQ(it->value, "11");
    auto it2 = it - 1;
    ASSERT_EQ(it2->value, "10");

    FDCore::AssociativeContainer<int, std::string> tmp;
    ASSERT_TRUE(tmp.empty());
}

TEST_F(FDCore_AssociativeContainer_int_str, EraseTest)
{
    size_t s = container.size();
    {
        ASSERT_EQ(container.erase(11), container.end());
        ASSERT_EQ(container.size(), s);
    }

    {
        container.erase(1);
        ASSERT_EQ(container.size(), s - 1);
    }

    {
        auto it = container.find(2);
        ASSERT_NE(container.erase(it), container.end());
        ASSERT_EQ(container.size(), s - 2);
    }

    auto it = container.begin();
    ++it;

    container.erase(it, container.end());
    ASSERT_EQ(container.size(), 1u);
}

TEST_F(FDCore_AssociativeContainer_int_str, EraseIfTest)
{
    size_t s = container.size();
    {
        ASSERT_EQ(container.erase_if([](const_cell_type &cell)
        {
            return cell.value == "11";
        }), container.end());
        ASSERT_EQ(container.size(), s);
    }

    {
        container.erase_if([](const_cell_type &cell)
        {
            return cell.key.key == 1;
        });
        ASSERT_EQ(container.size(), s - 1);
    }
}

TEST_F(FDCore_AssociativeContainer_int_str, EraseAllIfTest)
{
    size_t s = container.size();
    {
        ASSERT_EQ(container.erase_all_if([](const_cell_type &cell)
        {
            return cell.value == "11";
        }), 0u);
        ASSERT_EQ(container.size(), s);
    }

    {
        container.erase_all_if([](const_cell_type &cell)
        {
            return cell.key.key == 1;
        });
        ASSERT_EQ(container.size(), s - 2);
    }
}

TEST_F(FDCore_AssociativeContainer_int_str, CountTest)
{
    ASSERT_EQ(container.count(11), 0u);
    ASSERT_EQ(container.count(1), 2u);
}

TEST_F(FDCore_AssociativeContainer_int_str, CountIfTest)
{
    ASSERT_EQ(container.count_if([](const_cell_type &cell)
    {
        return cell.value == "11";
    }), 0u);
    ASSERT_EQ(container.count_if([](const_cell_type &cell)
    {
        return cell.value.size() == 1u;
    }), container.size() - 2u);
}

TEST_F(FDCore_AssociativeContainer_int_str, AtTest)
{
    {
        ASSERT_EQ(container.at(11), nullptr);
        auto *p = container.at(1);
        ASSERT_NE(p, nullptr);
        ASSERT_EQ(*p, "1");
    }

    {
        ASSERT_EQ(getContainer().at(12), nullptr);
        auto *p = getContainer().at(2);
        ASSERT_NE(p, nullptr);
        ASSERT_EQ(*p, "2");
    }

    {
        ASSERT_EQ(container[11], nullptr);
        auto *p = container[1];
        ASSERT_NE(p, nullptr);
        ASSERT_EQ(*p, "1");
    }

    {
        ASSERT_EQ(getContainer()[12], nullptr);
        auto *p = getContainer()[2];
        ASSERT_NE(p, nullptr);
        ASSERT_EQ(*p, "2");
    }
}

#ifdef NEED_UNDEF
#undef DEBUG
#undef NEED_UNDEF
#endif

#endif // ASSOCIATIVECONTAINER_TEST_H
