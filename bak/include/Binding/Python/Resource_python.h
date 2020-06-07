#ifndef FDCORE_RESOURCE_PYTHON_H
#define FDCORE_RESOURCE_PYTHON_H

#include <FDCore/BaseResource.h>
#include <FDCore/Binding/Python/Object_python.h>
#include <pybind11/embed.h>

namespace FDCore
{
    namespace Python
    {
        template<typename ResourceBase = FDCore::AbstractResource>
        class PYBIND11_EXPORT PyAbstractResource : public PyObject<ResourceBase>
        {
          public:
            /* Inherit the constructors */
            using PyObject<ResourceBase>::PyObject;

            std::string_view getResourceName() const override
            {
                PYBIND11_OVERLOAD_PURE(std::string_view, ResourceBase, getResourceName, );
            }

            void setResourceName(std::string_view resourceName) override
            {
                PYBIND11_OVERLOAD_PURE(void, ResourceBase, setResourceName, resourceName);
            }

            size_t getResourceHash() const override
            {
                PYBIND11_OVERLOAD_PURE(size_t, ResourceBase, getResourceHash, );
            }

            std::string_view getResourcePath() const override
            {
                PYBIND11_OVERLOAD_PURE(std::string_view, ResourceBase, getResourcePath, );
            }

            void setResourcePath(std::string_view path) override
            {
                PYBIND11_OVERLOAD_PURE(void, ResourceBase, setResourcePath, path);
            }

            bool load() override { PYBIND11_OVERLOAD_PURE(bool, ResourceBase, load, ); }

            bool isLoaded() const override
            {
                PYBIND11_OVERLOAD_PURE(bool, ResourceBase, isLoaded, );
            }

            void release() override { PYBIND11_OVERLOAD_PURE(void, ResourceBase, release, ); }
        };

        template<typename ResourceBase = FDCore::BaseResource>
        class PYBIND11_EXPORT PyResource : public PyAbstractResource<ResourceBase>
        {
          public:
            /* Inherit the constructors */
            using PyAbstractResource<ResourceBase>::PyAbstractResource;

            std::string_view getResourceName() const override
            {
                PYBIND11_OVERLOAD(std::string_view, ResourceBase, getResourceName, );
            }

            void setResourceName(std::string_view resourceName) override
            {
                PYBIND11_OVERLOAD(void, ResourceBase, setResourceName, resourceName);
            }

            size_t getResourceHash() const override
            {
                PYBIND11_OVERLOAD(size_t, ResourceBase, getResourceHash, );
            }

            std::string_view getResourcePath() const override
            {
                PYBIND11_OVERLOAD(std::string_view, ResourceBase, getResourcePath, );
            }

            void setResourcePath(std::string_view path) override
            {
                PYBIND11_OVERLOAD(void, ResourceBase, setResourcePath, path);
            }

            bool load() override { PYBIND11_OVERLOAD(bool, ResourceBase, load, ); }

            bool isLoaded() const override { PYBIND11_OVERLOAD(bool, ResourceBase, isLoaded, ); }

            void release() override { PYBIND11_OVERLOAD(void, ResourceBase, release, ); }
        };

        PYBIND11_EXPORT void bind_resource(pybind11::module &m);

        class PYBIND11_EXPORT PythonResourceWrapper : public FDCore::BaseResource
        {
          protected:
            pybind11::object m_self;

          public:
            PythonResourceWrapper() = default;
            PythonResourceWrapper(pybind11::object self);

            ~PythonResourceWrapper() override = default;

            void setSelf(pybind11::object self);
            pybind11::object getSelf();

            std::string_view getResourceName() const override;
            void setResourceName(std::string_view resourceName) override;
            size_t getResourceHash() const override;

            bool load() override;
            bool isLoaded() const override;
            void release() override;
        };
    } // namespace Python
} // namespace FDCore

#endif // FDCORE_RESOURCE_PYTHON_H
