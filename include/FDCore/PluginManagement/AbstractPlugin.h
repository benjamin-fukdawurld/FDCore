#ifndef FDCORE_ABSTRACTPLUGIN_H
#define FDCORE_ABSTRACTPLUGIN_H

#include <FDCore/ResourceManagement/AbstractResource.h>

namespace FDCore
{
    class AbstractPlugin : public AbstractResource
    {
      public:
        enum ApiEntryPointType
        {
            Variable,
            Factory
        };

        struct ApiEntryPoint
        {
            std::string symbolName;
            ApiEntryPointType type;
            bool isAlias;
        };

      public:
        using AbstractResource::AbstractResource;
        ~AbstractPlugin() override = default;

        std::vector<const char *> getTypeCodeHierarchy() const override;

        std::vector<size_t> getTypeCodeHashHierarchy() const override;

        const char *getTypeCode() const override;

        size_t getTypeCodeHash() const override;

        bool matchTypeCodeHash(size_t hash) const override;
    };
} // namespace FDCore

generateTypeCode(FDCore::AbstractPlugin);

#endif // FDCORE_ABSTRACTPLUGIN_H