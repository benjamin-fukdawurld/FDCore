#ifndef FDCORE_RESOURCEMANAGER_H
#define FDCORE_RESOURCEMANAGER_H

#include <FDCore/Common/ContiguousMap.h>
#include <FDCore/ResourceManagement/IResource.h>
#include <memory>
#include <string_view>
#include <utility>


namespace FDCore
{
    class ResourceManager
    {
      public:
        typedef std::unique_ptr<IResource> IResourcePtr;

      protected:
        ContiguousMap<std::string_view, IResourcePtr> m_resources;

      public:
        ResourceManager() = default;
        virtual ~ResourceManager();

        bool isEmpty() const { return m_resources.empty(); }
        size_t getNumberOfResources() const { return m_resources.size(); }
        bool contains(std::string_view resourceName) const
        {
            return m_resources[resourceName] != nullptr;
        }

        const IResource *getResource(std::string_view resourceName) const
        {
            return m_resources[resourceName]->get();
        }

        IResource *getResource(std::string_view resourceName)
        {
            return m_resources[resourceName]->get();
        }

        bool addResource(IResourcePtr &&res)
        {
            if(m_resources.contains(res->getResourceName()))
                return false;

            return m_resources.insert(res->getResourceName(), std::forward<IResourcePtr>(res)) !=
                   m_resources.end();
        }

        bool removeResource(std::string_view resourceName)
        {
            return m_resources.erase(resourceName);
        }

        void clearResources()
        {
            for(auto &res: m_resources)
                res.second->release();
        }
    };
} // namespace FDCore

#endif // FDCORE_RESOURCEMANAGER_H