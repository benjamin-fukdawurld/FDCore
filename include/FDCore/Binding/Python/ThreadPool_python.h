#ifndef THREADPOOL_PYTHON_H
#define THREADPOOL_PYTHON_H

#include <pybind11/embed.h>
#include <FDCore/ThreadPool.h>

namespace FDCore
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_threadpool(pybind11::module &m);
    }
}

#endif // THREADPOOL_PYTHON_H
