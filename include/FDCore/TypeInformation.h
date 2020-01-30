#ifndef TYPEINFORMATION_H
#define TYPEINFORMATION_H

#define generateTypeCodeWithName(type, name) \
namespace FDCore \
{ \
    template<> \
    struct TypeCodeHelper<type> \
    { \
        static constexpr const char code[] = #name; \
        static size_t hash() \
        { \
            static const size_t hash = std::hash<std::string_view>()(code); \
            return hash; \
        } \
    }; \
} \

#define generateTypeCode(type) generateTypeCodeWithName(type, #type)

#define generateTemplateTypeCodeWithName(type, template_type, name) \
namespace FDCore \
{ \
    template<typename template_type> \
    struct TypeCodeHelper<type<template_type>> \
    { \
        static constexpr const char code[] = #name; \
        static size_t hash() \
        { \
            static const size_t hash = std::hash<std::string_view>()(code); \
            return hash; \
        } \
    }; \
} \

#define generateTemplateTypeCode(type, template_type) \
    generateTemplateTypeCodeWithName(type, template_type, type<template_type>)

namespace FDCore
{
    template<typename T>
    struct TypeCodeHelper {};
}

#endif // TYPEINFORMATION_H