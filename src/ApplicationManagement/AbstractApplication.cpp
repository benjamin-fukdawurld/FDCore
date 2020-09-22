#include <FDCore/ApplicationManagement/AbstractApplication.h>

std::vector<const char *> FDCore::AbstractApplication::getTypeCodeHierarchy() const
{
    auto result = FDCore::Object::getTypeCodeHierarchy();
    result.push_back(FDCore::TypeCodeHelper<FDCore::AbstractPlugin>::code);
    return result;
}

std::vector<size_t> FDCore::AbstractApplication::getTypeCodeHashHierarchy() const
{
    auto result = FDCore::Object::getTypeCodeHashHierarchy();
    result.push_back(FDCore::TypeCodeHelper<FDCore::AbstractPlugin>::hash());
    return result;
}

const char *FDCore::AbstractApplication::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDCore::AbstractPlugin>::code;
}

size_t FDCore::AbstractApplication::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDCore::AbstractApplication>::hash();
}

bool FDCore::AbstractApplication::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDCore::AbstractApplication>::hash() ||
           FDCore::Object::matchTypeCodeHash(hash);
}