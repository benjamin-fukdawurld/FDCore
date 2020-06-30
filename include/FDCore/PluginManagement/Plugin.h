#ifndef FDCORE_PLUGIN_H
#define FDCORE_PLUGIN_H

#include <FDCore/PluginManagement/AbstractPlugin.h>
#include <boost/dll/alias.hpp>
#include <boost/dll/import.hpp>
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

        bool hasSymbol(std::string_view symbol) override { return m_library.has(symbol); }

        std::string_view getPath() { return m_path; }

        bool load(std::any data)
        {
            m_library.load(boost::dll::fs::path(m_path), boost::dll::load_mode::append_decorations);
            const ApiEntryPoint *entryPoint = nullptr;
            if(!data.has_value() ||
               (entryPoint = std::any_cast<const ApiEntryPoint *>(data)) == nullptr)
                return importWithoutData();

            if(entryPoint->type == Variable)
                return importVariable(entryPoint);

            if(entryPoint->type == Factory)
                return importFactory(entryPoint);

            return false;
        }

        bool isLoaded() const { return m_plugin; }

        void release() { m_plugin.reset(); }

        std::vector<const char *> getTypeCodeHierarchy() const override;

        std::vector<size_t> getTypeCodeHashHierarchy() const override;

        const char *getTypeCode() const override;

        size_t getTypeCodeHash() const override;

        bool matchTypeCodeHash(size_t hash) const override;

      private:
        bool importWithoutData()
        {
            m_plugin = boost::dll::import<PluginApi>(m_library, m_name);

            return plugin.get() != 0;
        }

        bool importVariable(ApiEntryPoint *entryPoint)
        {
            if(entryPoint->isAlias)
                m_plugin = boost::dll::import_alias<PluginApi>(m_library, entryPoint->symbolName);
            else
                m_plugin = boost::dll::import<PluginApi>(m_library, entryPoint->symbolName);

            return plugin.get() != 0;
        }

        bool importFactory(ApiEntryPoint *entryPoint)
        {
            PluginFactory factory;
            if(entryPoint->isAlias)
                factory =
                  boost::dll::import_alias<plugin_factory>(m_library, entryPoint->symbolName);
            else
                factory = boost::dll::import<plugin_factory>(m_library, entryPoint->symbolName);

            if(!factory)
                return false;

            m_plugin = factory();

            return plugin.get() != 0;
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