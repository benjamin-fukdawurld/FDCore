#ifndef FDCORE_ABSTRACTRESOURCE_H
#define FDCORE_ABSTRACTRESOURCE_H

#include <FDCore/ResourceManagement/IResource.h>
#include <string>

namespace FDCore
{
    class FD_EXPORT AbstractResource : IResource
    {
      private:
        std::string m_resourceName;
        size_t m_resourceHash;

      public:
        AbstractResource(std::string_view name = "");
        ~AbstractResource() override = default;

        std::string_view getResourceName() const override;
        size_t getResourceHash() const override;

        std::vector<const char *> getTypeCodeHierarchy() const override;

        std::vector<size_t> getTypeCodeHashHierarchy() const override;

        const char *getTypeCode() const override;

        size_t getTypeCodeHash() const override;

        bool matchTypeCodeHash(size_t hash) const override;

      protected:
        void setResourceName(std::string_view name);
    };
} // namespace FDCore

generateTypeCode(FDCore::AbstractResource);

#endif // FDCORE_ABSTRACTRESOURCE_H