#include <FDCore/PluginManagement/AbstractPlugin.h>

std::vector<const char *> FDCore::AbstractPlugin::getTypeCodeHierarchy() const
{
    auto result = FDCore::AbstractResource::getTypeCodeHierarchy();
    result.push_back(FDCore::TypeCodeHelper<FDCore::AbstractPlugin>::code);
    return result;
}

std::vector<size_t> FDCore::AbstractPlugin::getTypeCodeHashHierarchy() const
{
    auto result = FDCore::AbstractResource::getTypeCodeHashHierarchy();
    result.push_back(FDCore::TypeCodeHelper<FDCore::AbstractPlugin>::hash());
    return result;
}

const char *FDCore::AbstractPlugin::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDCore::AbstractPlugin>::code;
}

size_t FDCore::AbstractPlugin::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDCore::AbstractPlugin>::hash();
}

bool FDCore::AbstractPlugin::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDCore::AbstractPlugin>::hash() ||
           FDCore::AbstractResource::matchTypeCodeHash(hash);
}