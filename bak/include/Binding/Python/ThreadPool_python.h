#ifndef FDCORE_THREADPOOL_PYTHON_H
#define FDCORE_THREADPOOL_PYTHON_H

#include <FDCore/ThreadPool.h>
#include <pybind11/embed.h>

namespace FDCore
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_threadpool(pybind11::module &m);
    }
} // namespace FDCore

#endif // FDCORE_THREADPOOL_PYTHON_H
