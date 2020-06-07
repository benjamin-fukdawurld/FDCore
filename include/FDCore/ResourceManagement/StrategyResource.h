#ifndef FDCORE_STRATEGYRESOURCE_H
#define FDCORE_STRATEGYRESOURCE_H

#include <FDCore/ResourceManagement/AbstractResource.h>
#include <string>

namespace FDCore
{
    template<typename T>
    class StrategyResource : AbstractResource
    {
      public:
        typedef T resource_type;

      private:
        resource_type m_resource;
        std::function<bool(resource_type &, std::any)> m_loadStrategy;
        std::function<bool(resource_type &)> m_isLoadedStrategy;
        std::function<void(resource_type &)> m_releaseStrategy;

      public:
        StrategyResource(std::string_view name = "");
        ~StrategyResource() override = default;

        bool load(std::any data) override;
        bool isLoaded() const override;
        void release() override;

        std::vector<const char *> getTypeCodeHierarchy() const override;

        std::vector<size_t> getTypeCodeHashHierarchy() const override;

        const char *getTypeCode() const override;

        size_t getTypeCodeHash() const override;

        bool matchTypeCodeHash(size_t hash) const override;
    };
} // namespace FDCore

template<typename T>
FDCore::StrategyResource<T>::StrategyResource(std::string_view name) : AbstractResource(name)
{
}

template<typename T>
bool FDCore::StrategyResource<T>::load(std::any data)
{
    return m_loadStrategy(m_resource, data);
}


template<typename T>
bool FDCore::StrategyResource<T>::isLoaded() const
{
    return m_isLoadedStrategy(m_resource);
}

template<typename T>
void FDCore::StrategyResource<T>::release() override
{
    return m_releaseStrategy(m_resource);
}

template<typename T>
std::vector<const char *> FDCore::StrategyResource<T>::getTypeCodeHierarchy() const
{
    return { FDCore::TypeCodeHelper<FDCore::StrategyResource<T>>::code };
}

template<typename T>
std::vector<size_t> FDCore::StrategyResource<T>::getTypeCodeHashHierarchy() const
{
    return { FDCore::TypeCodeHelper<FDCore::StrategyResource<T>>::hash() };
}

template<typename T>
const char *FDCore::StrategyResource<T>::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDCore::StrategyResource<T>>::code;
}

template<typename T>
size_t FDCore::StrategyResource<T>::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDCore::StrategyResource<T>>::hash();
}

template<typename T>
bool FDCore::StrategyResource<T>::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDCore::StrategyResource<T>>::hash() ||
           FDCore::AbstractResource::matchTypeCodeHash(hash);
}

#endif // FDCORE_STRATEGYRESOURCE_H