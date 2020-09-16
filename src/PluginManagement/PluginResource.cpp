#include <FDCore/PluginManagement/PluginResource.h>

bool FDCore::PluginResource::isValid() const
{
    return m_plugin != nullptr && m_plugin->isLoaded() && m_resource != nullptr;
}

std::string_view FDCore::PluginResource::getResourceName() const
{
    if(!isValid())
        return "";

    return m_resource->getResourceName();
}
size_t FDCore::PluginResource::getResourceHash() const
{
    if(!isValid())
        return 0;

    return m_resource->getResourceHash();
}

bool FDCore::PluginResource::load(std::any /*data*/)
{
    if(!isValid())
        return false;

    return m_resource->load();
}

bool FDCore::PluginResource::isLoaded() const
{
    if(!isValid())
        return false;

    return m_resource->isLoaded();
}

void FDCore::PluginResource::release()
{
    if(!isValid())
        return;

    m_resource->release();
}

std::vector<const char *> FDCore::PluginResource::getTypeCodeHierarchy() const
{
    auto result = FDCore::IResource::getTypeCodeHierarchy();
    result.push_back(FDCore::TypeCodeHelper<FDCore::PluginResource>::code);
    return result;
}

std::vector<size_t> FDCore::PluginResource::getTypeCodeHashHierarchy() const
{
    auto result = FDCore::IResource::getTypeCodeHashHierarchy();
    result.push_back(FDCore::TypeCodeHelper<FDCore::PluginResource>::hash());
    return result;
}

const char *FDCore::PluginResource::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDCore::PluginResource>::code;
}

size_t FDCore::PluginResource::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDCore::PluginResource>::hash();
}

bool FDCore::PluginResource::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDCore::PluginResource>::hash() ||
           FDCore::IResource::matchTypeCodeHash(hash);
}