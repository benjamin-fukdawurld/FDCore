#ifndef FDCORE_ABSTRACTRESOURCE_H
#define FDCORE_ABSTRACTRESOURCE_H

#include <FDCore/ComparableTrait.h>
#include <FDCore/Object.h>

namespace FDCore
{
    class FD_EXPORT AbstractResource :
        public Object,
        public ComparableTrait<AbstractResource, AbstractResource>
    {
      public:
        AbstractResource() = default;

        AbstractResource(AbstractResource &&res) = default;
        AbstractResource(const AbstractResource &res) = delete;

        ~AbstractResource() override = default;

        AbstractResource &operator=(AbstractResource &&res) = default;
        AbstractResource &operator=(const AbstractResource &res) = delete;

        virtual std::string_view getResourceName() const = 0;
        virtual void setResourceName(std::string_view resourceName) = 0;
        virtual size_t getResourceHash() const = 0;

        virtual std::string_view getResourcePath() const = 0;
        virtual void setResourcePath(std::string_view path) = 0;

        virtual bool load() = 0;
        virtual bool isLoaded() const = 0;
        virtual void release() = 0;

        int64_t compare(const AbstractResource &other) const
        {
            return static_cast<int64_t>(getResourceHash()) -
                   static_cast<int64_t>(other.getResourceHash());
        }

        const char *getTypeCode() const override;

        size_t getTypeCodeHash() const override;

        bool matchTypeCodeHash(size_t hash) const override;
    };
} // namespace FDCore

generateTypeCode(FDCore::AbstractResource);

#endif // FDCORE_ABSTRACTRESOURCE_H
