#include <FDCore/AbstractResource.h>

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
    return hash == FDCore::TypeCodeHelper<FDCore::AbstractResource>::hash()
            || FDCore::Object::matchTypeCodeHash(hash);
}
