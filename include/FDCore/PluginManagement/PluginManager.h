#ifndef FDCORE_PLUGINMANAGER_H
#define FDCORE_PLUGINMANAGER_H

#include <FDCore/PluginManagement/AbstractPlugin.h>
#include <boost/dll/shared_library.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

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

        static bool isInLibrary(const boost::dll::shared_library &lib, std::string_view symbol)
        {
            return lib.has(symbol.data());
        }

        static bool isInLibrary(std::string_view libPath, std::string_view symbol)
        {
            return isInLibrary(
              boost::dll::shared_library(boost::dll::fs::path(libPath.data()),
                                         boost::dll::load_mode::append_decorations),
              symbol);
        }

        static std::unordered_map<std::string, bool> isInLibraries(
          const std::vector<std::string_view> &libsPath, std::string_view symbol)
        {
            std::unordered_map<std::string, bool> result;
            for(const std::string_view &path: libsPath)
                result[path.data()] = isInLibrary(path, symbol);

            return result;
        }

        static std::unordered_map<std::string, boost::dll::shared_library> loadIfContainsSymbol(
          const std::vector<std::string_view> &libsPath, std::string_view symbol)
        {
            std::unordered_map<std::string, boost::dll::shared_library> result;
            for(const std::string_view &path: libsPath)
            {
                boost::dll::shared_library lib(boost::dll::fs::path(path.data()),
                                               boost::dll::load_mode::append_decorations);
                if(isInLibrary(lib, symbol))
                    result[path.data()] = std::move(lib);
            }

            return result;
        }

        AbstractPlugin *getPlugin(std::string_view name);
        const AbstractPlugin *getPlugin(std::string_view name) const;
    };
} // namespace FDCore

#endif // FDCORE_PLUGINMANAGER_H