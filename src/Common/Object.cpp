#include <FDCore/Common/Object.h>

std::vector<const char *> FDCore::Object::getTypeCodeHierarchy() const
{
    return { FDCore::TypeCodeHelper<FDCore::Object>::code };
}

std::vector<size_t> FDCore::Object::getTypeCodeHashHierarchy() const
{
    return { FDCore::TypeCodeHelper<FDCore::Object>::hash() };
}

const char *FDCore::Object::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDCore::Object>::code;
}

size_t FDCore::Object::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDCore::Object>::hash();
}

bool FDCore::Object::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDCore::Object>::hash();
}
