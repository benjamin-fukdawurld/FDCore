#ifndef FDCORE_TYPEINFORMATION_H
#define FDCORE_TYPEINFORMATION_H

#include <functional>

#define generateTypeCodeWithName(type, name)                                    \
    namespace FDCore                                                            \
    {                                                                           \
        template<>                                                              \
        struct TypeCodeHelper<type>                                             \
        {                                                                       \
            static constexpr const char *const code = name;                     \
            static size_t hash()                                                \
            {                                                                   \
                static const size_t hash = std::hash<std::string_view>()(code); \
                return hash;                                                    \
            }                                                                   \
        };                                                                      \
    }

#define generateTypeCode(type) generateTypeCodeWithName(type, #type)

#define generateTemplateTypeCodeWithName(type, template_type, name)             \
    namespace FDCore                                                            \
    {                                                                           \
        template<typename(template_type)>                                       \
          struct TypeCodeHelper<(type) < (template_type)> >                     \
        {                                                                       \
            static constexpr const char code[] = name;                          \
            static size_t hash()                                                \
            {                                                                   \
                static const size_t hash = std::hash<std::string_view>()(code); \
                return hash;                                                    \
            }                                                                   \
        };                                                                      \
    }

#define generateTemplateTypeName_str(name) #name
#define generateTemplateTypeName(type, template_type) \
    generateTemplateTypeName_str((type) < template_type >)
#define generateTemplateTypeCode(type, template_type)     \
    generateTemplateTypeCodeWithName(type, template_type, \
                                     generateTemplateTypeName(type, template_type))

namespace FDCore
{
    template<typename T>
    struct TypeCodeHelper
    {
    };
} // namespace FDCore

#endif // FDCORE_TYPEINFORMATION_H
