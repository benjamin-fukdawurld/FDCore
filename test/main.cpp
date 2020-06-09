#include <FDCore/Common/ContiguousMap.h>
#include <FDCore/Common/ContiguousSet.h>
#include <cassert>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    FDCore::ContiguousMap<std::string, int> m;
    m.insert("test", 0);
    m.insert("test", 1);
    m.insert("test", 2);

    for(const auto &[key, value]: m)
        std::cout << key << ": " << value << std::endl;

    assert(m.find("test")->second == 0);
    assert(m.find_last("test")->second == 2);
    assert(m.find_all("test").size() == 3);

    return 0;
}