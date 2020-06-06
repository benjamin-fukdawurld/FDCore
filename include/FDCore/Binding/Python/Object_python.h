#ifndef FDCORE_OBJECT_PYTHON_H
#define FDCORE_OBJECT_PYTHON_H

#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <FDCore/Object.h>

namespace FDCore
{
    namespace Python
    {
        template<typename ObjectBase = FDCore::Object>
        class PYBIND11_EXPORT PyObject : public ObjectBase
        {
            public:
                /* Inherit the constructors */
                using ObjectBase::ObjectBase;

                std::vector<const char*> getTypeCodeHierarchy() override
                {
                    PYBIND11_OVERLOAD(
                        std::vector<const char*>, /* Return type */
                        ObjectBase,      /* Parent class */
                        getTypeCodeHierarchy,         /* Name of function in C++ (must match Python name) */
                    );
                }

                std::vector<size_t> getTypeCodeHashHierarchy() override
                {
                    PYBIND11_OVERLOAD(
                        std::vector<size_t>, /* Return type */
                        ObjectBase,      /* Parent class */
                        getTypeCodeHashHierarchy,         /* Name of function in C++ (must match Python name) */
                    );
                }

                const char *getTypeCode() const override {
                    PYBIND11_OVERLOAD(
                        const char *, /* Return type */
                        ObjectBase,      /* Parent class */
                        getTypeCode,         /* Name of function in C++ (must match Python name) */
                    );
                }

                size_t getTypeCodeHash() const override {
                    PYBIND11_OVERLOAD(
                        size_t, /* Return type */
                        ObjectBase,      /* Parent class */
                        getTypeCodeHash,          /* Name of function in C++ (must match Python name) */
                    );
                }

                bool matchTypeCodeHash(size_t hash) const override {
                    PYBIND11_OVERLOAD(
                        bool, /* Return type */
                        ObjectBase,      /* Parent class */
                        matchTypeCodeHash,          /* Name of function in C++ (must match Python name) */
                        hash      /* Argument(s) */
                    );
                }
        };

        PYBIND11_EXPORT void bind_object(pybind11::module &m);
    }
}

#endif // FDCORE_OBJECT_PYTHON_H
