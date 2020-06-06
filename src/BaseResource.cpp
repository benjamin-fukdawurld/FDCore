#include <FDCore/BaseResource.h>


FDCore::BaseResource::BaseResource() :
    BaseResource("")
{}

FDCore::BaseResource::BaseResource(std::string_view resourceName):
    BaseResource(resourceName, "")
{}

FDCore::BaseResource::BaseResource(std::string_view resourceName, std::string_view resourcePath):
    AbstractResource(),
    m_resourceName(resourceName),
    m_resourcePath(resourcePath),
    m_resourceHash(std::hash<std::string>()(m_resourceName))
{}

FDCore::BaseResource::BaseResource(FDCore::BaseResource &&res):
    m_resourceName(std::move(res.m_resourceName)),
    m_resourcePath(std::move(res.m_resourcePath)),
    m_resourceHash(res.m_resourceHash)
{}

std::string_view FDCore::BaseResource::getResourcePath() const
{
    return m_resourcePath;
}

void FDCore::BaseResource::setResourcePath(std::string_view path)
{
    m_resourcePath = path;
}

FDCore::BaseResource &FDCore::BaseResource::operator=(FDCore::BaseResource &&res)
{
    release();
    m_resourceHash = res.m_resourceHash;
    m_resourceName = std::move(res.m_resourceName);
    return *this;
}

std::string_view FDCore::BaseResource::getResourceName() const
{
    return m_resourceName;
}

void FDCore::BaseResource::setResourceName(std::string_view resourceName)
{
    m_resourceName = resourceName;
    m_resourceHash = std::hash<std::string>()(m_resourceName);
}

size_t FDCore::BaseResource::getResourceHash() const
{
    return  m_resourceHash;
}

const char *FDCore::BaseResource::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDCore::BaseResource>::code;
}

size_t FDCore::BaseResource::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDCore::BaseResource>::hash();
}

bool FDCore::BaseResource::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDCore::BaseResource>::hash()
            || FDCore::AbstractResource::matchTypeCodeHash(hash);
}
