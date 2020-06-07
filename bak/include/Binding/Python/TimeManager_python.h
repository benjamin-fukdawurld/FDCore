#ifndef FDCORE_TIMEMANAGER_PYTHON_H
#define FDCORE_TIMEMANAGER_PYTHON_H

#include <FDCore/TimeManager.h>
#include <pybind11/embed.h>

namespace FDCore
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_timemanager(pybind11::module &m);
    }
} // namespace FDCore

#endif // FDCORE_TIMEMANAGER_PYTHON_H
