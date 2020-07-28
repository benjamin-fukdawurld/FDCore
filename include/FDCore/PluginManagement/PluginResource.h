#ifndef FDCORE_PLUGINRESOURCE_H
#define FDCORE_PLUGINRESOURCE_H

#include <FDCore/PluginManagement/AbstractPlugin.h>
#include <FDCore/ResourceManagement/IResource.h>

namespace FDCore
{
    class FD_EXPORT PluginResource : public IResource
    {
      private:
        AbstractPlugin *m_plugin;
        IResource *m_resource;

      public:
        PluginResource() : PluginResource(nullptr) {}
        PluginResource(AbstractPlugin *plugin) : PluginResource(plugin, nullptr) {}
        PluginResource(AbstractPlugin *plugin, IResource *resource) :
            m_plugin(plugin),
            m_resource(resource)
        {
        }

        bool hasPlugin() { return m_plugin != nullptr; }
        AbstractPlugin *getPlugin() { return m_plugin; }
        const AbstractPlugin *getPlugin() const { return m_plugin; }
        void setPlugin(AbstractPlugin *plugin) { m_plugin = plugin; }

        bool hasResource() { return m_resource != nullptr; }
        IResource *getResource() { return m_resource; }
        const IResource *getResource() const { return m_resource; }
        void setResource(IResource *resource) { m_resource = resource; }

        bool isValid() const;

        operator bool() const { return isValid(); }
        IResource *operator->() { return m_resource; }
        const IResource *operator->() const { return m_resource; }

        std::string_view getResourceName() const override;
        size_t getResourceHash() const override;

        bool load(std::any data = {}) override;
        bool isLoaded() const override;
        void release() override;

        std::vector<const char *> getTypeCodeHierarchy() const override;

        std::vector<size_t> getTypeCodeHashHierarchy() const override;

        const char *getTypeCode() const override;

        size_t getTypeCodeHash() const override;

        bool matchTypeCodeHash(size_t hash) const override;
    };
} // namespace FDCore

generateTypeCode(FDCore::PluginResource);

#endif // FDCORE_PLUGINRESOURCE_H