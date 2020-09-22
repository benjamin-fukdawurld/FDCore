#ifndef FDCORE_PLUGINBINDER_H
#define FDCORE_PLUGINBINDER_H

#include <FDCore/ApplicationManagement/AbstractApplication.h>
#include <FDCore/PluginManagement/PluginResource.h>

namespace FDCore
{
    class AbstractPluginBinder
    {
        virtual PluginResource bind(AbstractApplication &app) = 0;
    };
} // namespace FDCore

#endif // FDCORE_PLUGINBINDER_H