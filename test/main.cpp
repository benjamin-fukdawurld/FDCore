#include <FDCore/Common/ContiguousMap.h>
#include <FDCore/Common/ContiguousSet.h>
#include <FDCore/Common/Identifiable.h>
#include <FDCore/Log/Logger.h>
#include <FDCore/ResourceManagement/ResourceManager.h>
#include <cassert>
#include <iostream>
#include <string>

int main(int, char **)
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

    FDCore::Identifiable<int> int_id;
    FDCore::Identifiable<uintptr_t> ptr_id;

    assert(int_id.getId() == 1);
    assert(ptr_id.getId() == reinterpret_cast<uintptr_t>(&ptr_id));

    FDCore::ResourceManager mgr;
    FDCore::Logger logger;

    logger(FDCore::Debug) << "test log"
                          << " must be on the same line";

    return 0;
}