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
      protected:
        std::unique_ptr<PluginApi> m_plugin;
        std::string m_path;

      public:
        Plugin(std::string_view name, std::string_view path) : AbstractPlugin(name), m_path(path) {}

        ~Plugin() override = default;

        std::string_view getPath() { return m_path; }

        bool load(std::any data)
        {
            m_plugin = dll::import<PluginApi>(boost::dll::fs::path(m_path), m_name,
                                              dll::load_mode::append_decorations);

            return m_plugin;
        }

        bool isLoaded() const { return m_plugin; }

        void release() { m_plugin.reset(); }

        std::vector<const char *> getTypeCodeHierarchy() const override;

        std::vector<size_t> getTypeCodeHashHierarchy() const override;

        const char *getTypeCode() const override;

        size_t getTypeCodeHash() const override;

        bool matchTypeCodeHash(size_t hash) const override;
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