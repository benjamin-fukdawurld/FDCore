#include <FDCore/Binding/Python/Resource_python.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

void FDCore::Python::bind_resource(pybind11::module &m)
{
    /*py::class_<FDCore::AbstractResource, FDCore::Python::PyAbstractResource<>>(m, "AbstractResource")
        .def(py::init_alias())
        .def("getResourceName", &FDCore::AbstractResource::getResourceName)
        .def("setResourceName", &FDCore::AbstractResource::setResourceName)
        .def("getResourceHash", &FDCore::AbstractResource::getResourceHash)
        .def("getResourcePath", &FDCore::AbstractResource::getResourcePath)
        .def("setResourcePath", &FDCore::AbstractResource::setResourcePath)
        .def("isLoaded", &FDCore::AbstractResource::isLoaded)
        .def("load", &FDCore::AbstractResource::load)
        .def("release", &FDCore::AbstractResource::release)
        .def_property_readonly("resourceHash", &FDCore::AbstractResource::getResourceHash)
        .def_property("resourceName", &FDCore::AbstractResource::getResourceName, &FDCore::AbstractResource::setResourceName)
        .def("compare", &FDCore::AbstractResource::compare)
    ;

    py::class_<FDCore::BaseResource, FDCore::Python::PyResource<>>(m, "BaseResource")
        .def(py::init_alias<>())
        .def(py::init_alias<std::string_view>())
        .def(py::init_alias<std::string_view, std::string_view>())
        .def("getResourceName", &FDCore::BaseResource::getResourceName)
        .def("setResourceName", &FDCore::BaseResource::setResourceName)
        .def("getResourceHash", &FDCore::BaseResource::getResourceHash)
        .def("getResourcePath", &FDCore::BaseResource::getResourcePath)
        .def("setResourcePath", &FDCore::BaseResource::setResourcePath)
        .def("isLoaded", &FDCore::BaseResource::isLoaded)
        .def("load", &FDCore::BaseResource::load)
        .def("release", &FDCore::BaseResource::release)
        .def_property_readonly("resourceHash", &FDCore::BaseResource::getResourceHash)
        .def_property("resourceName", &FDCore::BaseResource::getResourceName, &FDCore::BaseResource::setResourceName)
        .def("compare", &FDCore::AbstractResource::compare)
    ;*/
}

std::string_view FDCore::Python::PythonResourceWrapper::getResourceName() const
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "resourceName"))
        return m_self.attr("resourceName").cast<std::string>();

    return "";
}

void FDCore::Python::PythonResourceWrapper::setResourceName(std::string_view resourceName)
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "resourceName"))
        m_self.attr("resourceName") = resourceName;
}

size_t FDCore::Python::PythonResourceWrapper::getResourceHash() const
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "resourceHash"))
        return m_self.attr("resourceHash").cast<size_t>();

    return 0;
}

bool FDCore::Python::PythonResourceWrapper::load()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "load"))
        return m_self.attr("load")().cast<bool>();

    return false;
}

bool FDCore::Python::PythonResourceWrapper::isLoaded() const
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "isLoaded"))
        return m_self.attr("isLoaded")().cast<bool>();

    return false;
}

void FDCore::Python::PythonResourceWrapper::release()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "release"))
        m_self.attr("release")();
}
