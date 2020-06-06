#ifndef FDCORE_OBJECT_H
#define FDCORE_OBJECT_H

#include <FDCore/TypeInformation.h>

#include <FDCore/Macros.h>

namespace FDCore
{
    class FD_EXPORT Object
    {
        public:
            Object() = default;
            virtual ~Object() = default;

            template<typename T>
            bool is() const
            {
                return matchTypeCodeHash(FDCore::TypeCodeHelper<T>::hash());
            }

            template<typename T>
            T *as()
            {
                if(!is<T>())
                    return nullptr;

                return static_cast<T*>(this);
            }

            template<typename T>
            const T *as() const
            {
                if(!is<T>())
                    return nullptr;

                return static_cast<T*>(this);
            }

            virtual std::vector<const char*> getTypeCodeHierarchy();

            virtual std::vector<size_t> getTypeCodeHashHierarchy();

            virtual const char *getTypeCode() const;

            virtual size_t getTypeCodeHash() const;

            virtual bool matchTypeCodeHash(size_t hash) const;
    };
}

generateTypeCode(FDCore::Object);

#endif // FDCORE_OBJECT_H
