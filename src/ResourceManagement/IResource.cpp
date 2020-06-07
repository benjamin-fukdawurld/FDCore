#include <FDCore/ResourceManagement/IResource.h>

std::vector<const char *> FDCore::IResource::getTypeCodeHierarchy() const
{
    auto result = FDCore::Object::getTypeCodeHierarchy();
    result.push_back(FDCore::TypeCodeHelper<FDCore::IResource>::code);
    return result;
}

std::vector<size_t> FDCore::IResource::getTypeCodeHashHierarchy() const
{
    auto result = FDCore::Object::getTypeCodeHashHierarchy();
    result.push_back(FDCore::TypeCodeHelper<FDCore::IResource>::hash());
    return result;
}

const char *FDCore::IResource::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDCore::IResource>::code;
}

size_t FDCore::IResource::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDCore::IResource>::hash();
}

bool FDCore::IResource::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDCore::IResource>::hash() ||
           FDCore::Object::matchTypeCodeHash(hash);
}