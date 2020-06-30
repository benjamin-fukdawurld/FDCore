#ifndef FDCORE_PLUGINMANAGER_H
#define FDCORE_PLUGINMANAGER_H

#include <FDCore/PluginManagement/PluginManager.h>
#include <unordered_map>

namespace FDCore
{
    class PluginManager
    {
      public:
        typedef std::unique_ptr<AbstractPlugin> AbstractPluginPtr;

      protected:
        std::unordered_map<std::string_view, AbstractPlugin *> m_plugins;

      public:
        PluginManager() {}
        virtual ~PluginManager() = default;

        bool hasPlugin(std::string_view name) const
        {
            return m_plugins.find(name) != m_plugins.end();
        }

        AbstractPlugin *getPlugin(std::string_view name);
        const AbstractPlugin *getPlugin(std::string_view name) const;
    };
} // namespace FDCore

#endif // FDCORE_PLUGINMANAGER_H