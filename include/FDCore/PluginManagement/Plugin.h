#ifndef FDCORE_PLUGIN_H
#define FDCORE_PLUGIN_H

#include <FDCore/PluginManagement/AbstractPlugin.h>
#include <boost/dll/alias.hpp>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include <memory>

namespace FDCore
{
    template<typename PluginApi>
    class Plugin : public AbstractPlugin
    {
      public:
        typedef boost::dll::shared_library PluginLibrary;
        typedef boost::shared_ptr<PluginApi> PluginPointer;
        typedef boost::function<PluginPointer()> PluginFactory;

      protected:
        PluginLibrary m_library;
        PluginPointer m_plugin;
        std::string m_path;

      public:
        Plugin(std::string_view name, std::string_view path) : AbstractPlugin(name), m_path(path) {}

        ~Plugin() override = default;

        bool hasSymbol(std::string_view symbol) override { return m_library.has(symbol.data()); }

        template<typename T>
        T getSymbol(std::string_view symbol)
        {
            return m_library.get<T>(symbol.data());
        }

        template<typename T>
        T getSymbolAlias(std::string_view alias)
        {
            return m_library.get_alias<T>(alias.data());
        }

        std::string_view getPath() { return m_path; }

        PluginLibrary &getLibrary() { return m_library; }
        const PluginLibrary &getLibrary() const { return m_library; }

        PluginApi &getPlugin() { return *m_plugin; }
        const PluginApi &getPlugin() const { return *m_plugin; }

        PluginApi *operator->() { return m_plugin.get(); }
        const PluginApi *operator->() const { return m_plugin.get(); }

        bool load(std::any data = {}) override
        {
            m_library.load(boost::dll::fs::path(m_path), boost::dll::load_mode::append_decorations);
            ApiEntryPoint *entryPoint = nullptr;
            if(!data.has_value() || (entryPoint = std::any_cast<ApiEntryPoint *>(data)) == nullptr)
                return importWithoutData();

            if(entryPoint->type == Variable)
                return importVariable(entryPoint);

            if(entryPoint->type == Factory)
                return importFactory(entryPoint);

            return false;
        }

        bool isLoaded() const override { return m_library.is_loaded(); }

        void release() override
        {
            m_plugin.reset();
            m_library.unload();
        }

        std::vector<const char *> getTypeCodeHierarchy() const override;

        std::vector<size_t> getTypeCodeHashHierarchy() const override;

        const char *getTypeCode() const override;

        size_t getTypeCodeHash() const override;

        bool matchTypeCodeHash(size_t hash) const override;

      private:
        bool importWithoutData()
        {
            m_plugin = boost::dll::import_symbol<PluginApi>(m_library, getResourceName().data());

            return m_plugin.get() != 0;
        }

        bool importVariable(const ApiEntryPoint *entryPoint)
        {
            if(entryPoint->isAlias)
                m_plugin = boost::dll::import_alias<PluginApi>(m_library, entryPoint->symbolName);
            else
                m_plugin = boost::dll::import_symbol<PluginApi>(m_library, entryPoint->symbolName);

            return m_plugin.get() != 0;
        }

        bool importFactory(const ApiEntryPoint *entryPoint)
        {
            boost::shared_ptr<PluginFactory> factory;
            if(entryPoint->isAlias)
                factory =
                  boost::dll::import_alias<PluginFactory>(m_library, entryPoint->symbolName);
            else
                factory = boost::dll::import_symbol<PluginFactory>(m_library, entryPoint->symbolName);

            if(!factory)
                return false;

            m_plugin = (*factory)();

            return m_plugin.get() != 0;
        }
    };

    template<typename PluginApi>
    std::vector<const char *> Plugin<PluginApi>::getTypeCodeHierarchy() const
    {
        auto result = FDCore::AbstractPlugin::getTypeCodeHierarchy();
        result.push_back(FDCore::TypeCodeHelper<FDCore::Plugin<PluginApi>>::code);
        return result;
    }

    template<typename PluginApi>
    std::vector<size_t> Plugin<PluginApi>::getTypeCodeHashHierarchy() const
    {
        auto result = FDCore::AbstractPlugin::getTypeCodeHashHierarchy();
        result.push_back(FDCore::TypeCodeHelper<FDCore::Plugin<PluginApi>>::hash());
        return result;
    }

    template<typename PluginApi>
    const char *Plugin<PluginApi>::getTypeCode() const
    {
        return FDCore::TypeCodeHelper<FDCore::Plugin<PluginApi>>::code;
    }

    template<typename PluginApi>
    size_t Plugin<PluginApi>::getTypeCodeHash() const
    {
        return FDCore::TypeCodeHelper<FDCore::Plugin<PluginApi>>::hash();
    }

    template<typename PluginApi>
    bool Plugin<PluginApi>::matchTypeCodeHash(size_t hash) const
    {
        return hash == FDCore::TypeCodeHelper<FDCore::Plugin<PluginApi>>::hash() ||
               FDCore::AbstractPlugin::matchTypeCodeHash(hash);
    }
} // namespace FDCore

#endif // FDCORE_PLUGIN_H