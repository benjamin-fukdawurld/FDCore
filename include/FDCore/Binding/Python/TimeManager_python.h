#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <pybind11/embed.h>

#include <FDCore/TimeManager.h>

namespace FDCore
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_timemanager(pybind11::module &m);
    }
}

#endif // TIMEMANAGER_H
