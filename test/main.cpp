#include "Common/Common_test.h"
#include "PluginManagement/Plugin_test.h"
#include "PluginManagement/test_PluginApi.h"

#include <FDCore/ApplicationManagement/AbstractApplication.h>
#include <FDCore/Common/ContiguousSet.h>
#include <FDCore/Common/Identifiable.h>
#include <FDCore/Common/ObjectGuard.h>
#include <FDCore/Log/Logger.h>
#include <FDCore/PluginManagement/Plugin.h>
#include <FDCore/ResourceManagement/ResourceManager.h>
#include <cassert>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

generateTypeCode(FDCore::Plugin<FDCore::PluginApi>);
/*class Application : public FDCore::AbstractApplication
{
  private:
    std::vector<FDCore::AbstractPlugin *> m_plugins;

  public:
    Application() = default;
    bool init() override;
    void quit() override;
    int run(int argc, char **argv) override;

    void addPlugin(FDCore::AbstractPlugin *plugin) override;
};

bool Application::init()
{
    FDCore::Logger logger;
    logger(FDCore::Information) << "Initializing Application";

    logger(FDCore::Information) << "Application Initialized";

    return true;
}

void Application::quit()
{
    FDCore::Logger logger;
    logger(FDCore::Information) << "Quitting Application";

    logger(FDCore::Information) << "Application Quitted";
}

generateTypeCode(FDCore::Plugin<int>);

int Application::run(int, char **)
{
    FDCore::Plugin<FDCore::PluginApi> plugin("test_plugin", "FDCore_test_plugin");
    FDCore::AbstractPlugin::ApiEntryPoint entryPoint;
    entryPoint.type = FDCore::AbstractPlugin::Variable;
    entryPoint.symbolName = "plugin";
    std::any entryPointAny = &entryPoint;
    plugin.load(entryPointAny);
    assert(plugin.isLoaded());

    std::cout << "plugin->i : " << plugin->i << std::endl;
    std::cout << "plugin->pi : " << plugin->pi << std::endl;
    std::cout << std::boolalpha << "plugin->b : " << plugin->b << std::endl;
    std::cout << "plugin->c : " << plugin->c << std::endl;
    std::cout << "plugin->str : " << plugin->str << std::endl;

    std::cout << "plugin->f_i : " << plugin->f_i() << std::endl;
    std::cout << "plugin->f_f : " << plugin->f_f() << std::endl;
    std::cout << std::boolalpha << "plugin->f_b : " << plugin->f_b() << std::endl;
    std::cout << "plugin->f_c : " << plugin->f_c() << std::endl;
    std::cout << "plugin->f_str : " << plugin->f_str() << std::endl;

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

    plugin.release();

    return AbstractApplication::ExitSuccess;
}

void Application::addPlugin(FDCore::AbstractPlugin *plugin) { m_plugins.push_back(plugin); }*/

int main(int argc, char **argv)
{
    /*Application app;
    FDCore::ObjectGuard<Application> guard(app);
    return app.run(argc, argv);*/

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
