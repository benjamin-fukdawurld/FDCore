#include <FDCore/Common/ContiguousMap.h>
#include <FDCore/Common/ContiguousSet.h>
#include <FDCore/Common/Identifiable.h>
#include <FDCore/Log/Logger.h>
#include <FDCore/ResourceManagement/ResourceManager.h>
#include <cassert>
#include <iostream>
#include <string>

#include <FDCore/ApplicationManagement/AbstractApplication.h>

class Application : public FDCore::AbstractApplication
{
    private:
        std::vector<FDCore::AbstractPlugin*> m_plugins;

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

int Application::run(int, char **)
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

    return AbstractApplication::ExitSuccess;
}

void Application::addPlugin(FDCore::AbstractPlugin *plugin)
{
    m_plugins.push_back(plugin);
}

class ApplicationGuard
{
    private:
        FDCore::AbstractApplication &m_app;

    public:
        ApplicationGuard(FDCore::AbstractApplication &app) : m_app(app) { m_app.init(); }
        ~ApplicationGuard() { m_app.quit(); }
};

int main(int argc, char **argv)
{
    Application app;
    ApplicationGuard guard(app);
    return app.run(argc, argv);
}