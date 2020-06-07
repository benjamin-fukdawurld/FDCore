#ifndef FDCORE_BASERESSOURCE_H
#define FDCORE_BASERESSOURCE_H

#include <FDCore/AbstractResource.h>
#include <string>

namespace FDCore
{
    class FD_EXPORT BaseResource : public AbstractResource
    {
      private:
        std::string m_resourceName;
        std::string m_resourcePath;
        size_t m_resourceHash;

      public:
        BaseResource();
        explicit BaseResource(std::string_view resourceName);
        BaseResource(std::string_view resourceName, std::string_view resourcePath);

        BaseResource(BaseResource &&res);
        BaseResource(const BaseResource &res) = delete;

        ~BaseResource() override = default;

        std::string_view getResourcePath() const override;
        void setResourcePath(std::string_view path) override;

        BaseResource &operator=(BaseResource &&res);
        BaseResource &operator=(const BaseResource &res) = delete;


        std::string_view getResourceName() const override;
        void setResourceName(std::string_view resourceName) override;

        size_t getResourceHash() const override;

        const char *getTypeCode() const override;

        size_t getTypeCodeHash() const override;

        bool matchTypeCodeHash(size_t hash) const override;
    };
} // namespace FDCore

generateTypeCode(FDCore::BaseResource);

#endif // FDCORE_BASERESSOURCE_H
