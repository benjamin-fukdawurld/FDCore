#include <FDCore/ResourceManagement/AbstractResource.h>

FDCore::AbstractResource::AbstractResource(std::string_view name) : m_resourceHash(0)
{
    setResourceName(name);
}

std::string_view FDCore::AbstractResource::getResourceName() const { return m_resourceName; }

size_t FDCore::AbstractResource::getResourceHash() const { return m_resourceHash; }

void FDCore::AbstractResource::setResourceName(std::string_view name)
{
    m_resourceName = name;
    m_resourceHash = std::hash<std::string_view>()(m_resourceName);
}

std::vector<const char *> FDCore::AbstractResource::getTypeCodeHierarchy() const
{
    auto result = FDCore::IResource::getTypeCodeHierarchy();
    result.push_back(FDCore::TypeCodeHelper<FDCore::AbstractResource>::code);
    return result;
}

std::vector<size_t> FDCore::AbstractResource::getTypeCodeHashHierarchy() const
{
    auto result = FDCore::IResource::getTypeCodeHashHierarchy();
    result.push_back(FDCore::TypeCodeHelper<FDCore::AbstractResource>::hash());
    return result;
}

const char *FDCore::AbstractResource::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDCore::AbstractResource>::code;
}

size_t FDCore::AbstractResource::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDCore::AbstractResource>::hash();
}

bool FDCore::AbstractResource::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDCore::AbstractResource>::hash() ||
           FDCore::IResource::matchTypeCodeHash(hash);
}