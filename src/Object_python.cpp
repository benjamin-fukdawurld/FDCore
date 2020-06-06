#include <FDCore/Binding/Python/Object_python.h>

namespace py = pybind11;

void FDCore::Python::bind_object(pybind11::module &m)
{
    auto obj = py::class_<FDCore::Object, FDCore::Python::PyObject<>>(m, "Object")
            .def(py::init_alias());
}
