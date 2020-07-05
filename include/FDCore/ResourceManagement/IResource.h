#ifndef FDCORE_IRESOURCE_H
#define FDCORE_IRESOURCE_H

#include <FDCore/Common/Macros.h>
#include <FDCore/Common/Object.h>
#include <any>
#include <string_view>

namespace FDCore
{
    class FD_EXPORT IResource : public Object
    {
      public:
        IResource() = default;
        virtual ~IResource() = default;

        virtual std::string_view getResourceName() const = 0;
        virtual size_t getResourceHash() const = 0;

        virtual bool load(std::any data = {}) = 0;
        virtual bool isLoaded() const = 0;
        virtual void release() = 0;

        std::vector<const char *> getTypeCodeHierarchy() const override;

        std::vector<size_t> getTypeCodeHashHierarchy() const override;

        const char *getTypeCode() const override;

        size_t getTypeCodeHash() const override;

        bool matchTypeCodeHash(size_t hash) const override;
    };
} // namespace FDCore

namespace std
{
    template<>
    struct hash<FDCore::IResource>
    {
        size_t operator()(const FDCore::IResource &res) { return res.getResourceHash(); }
    };

    template<>
    struct less<FDCore::IResource>
    {
        bool operator()(const FDCore::IResource &a, const FDCore::IResource &b)
        {
            return a.getResourceHash() < b.getResourceHash();
        }
    };

    template<>
    struct less_equal<FDCore::IResource>
    {
        bool operator()(const FDCore::IResource &a, const FDCore::IResource &b)
        {
            return a.getResourceHash() <= b.getResourceHash();
        }
    };

    template<>
    struct greater<FDCore::IResource>
    {
        bool operator()(const FDCore::IResource &a, const FDCore::IResource &b)
        {
            return a.getResourceHash() > b.getResourceHash();
        }
    };

    template<>
    struct greater_equal<FDCore::IResource>
    {
        bool operator()(const FDCore::IResource &a, const FDCore::IResource &b)
        {
            return a.getResourceHash() >= b.getResourceHash();
        }
    };

    template<>
    struct equal_to<FDCore::IResource>
    {
        bool operator()(const FDCore::IResource &a, const FDCore::IResource &b)
        {
            return a.getResourceHash() == b.getResourceHash();
        }
    };

    template<>
    struct not_equal_to<FDCore::IResource>
    {
        bool operator()(const FDCore::IResource &a, const FDCore::IResource &b)
        {
            return a.getResourceHash() != b.getResourceHash();
        }
    };
} // namespace std

generateTypeCode(FDCore::IResource);

#endif // FDCORE_IRESOURCE_H