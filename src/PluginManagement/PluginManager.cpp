#include <FDCore/PluginManagement/PluginManager.h>

AbstractPlugin *FDCore::PluginManager::getPlugin(std::string_view name)
{
    auto it = m_plugins.find(name);
    if(it == m_plugins.end())
        return nullptr;
    return it;
}

const AbstractPlugin *FDCore::PluginManager::getPlugin(std::string_view name) const
{
    auto it = m_plugins.find(name);
    if(it == m_plugins.end())
        return nullptr;
    return it;
}