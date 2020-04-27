#ifndef FDCOREPYTHON_H
#define FDCOREPYTHON_H

#include <pybind11/embed.h>

#include <FDCore/Binding/Python/ThreadPool_python.h>
#include <FDCore/Binding/Python/TimeManager_python.h>

extern pybind11::detail::embedded_module PyFDCore;
PYBIND11_EMBEDDED_MODULE(PyFDCore, m)
{
    FDCore::Python::bind_threadpool(m);
    FDCore::Python::bind_timemanager(m);
}

#endif // FDCOREPYTHON_H
