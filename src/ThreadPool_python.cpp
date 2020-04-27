#include <FDCore/Binding/Python/ThreadPool_python.h>

namespace py = pybind11;

void FDCore::Python::bind_threadpool(pybind11::module &m)
{
    py::class_<FDCore::ThreadPool>(m, "ThreadPool")
        .def(py::init())
        .def(py::init<size_t>())
        .def("enqueue", [](FDCore::ThreadPool &pool, py::function func, py::args args, py::kwargs kwargs)
        {
            return pool.enqueue([](py::function func, py::args args, py::kwargs kwargs)
            {
                pybind11::gil_scoped_acquire acquire;
                return func(args, kwargs);
            }, func, args, kwargs);
        })
        .def_property("numberOfThreads", &FDCore::ThreadPool::getNumberOfThreads, &FDCore::ThreadPool::setNumberOfThreads);
}
