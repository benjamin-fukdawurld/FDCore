#ifndef FDCORE_ABSTRACTAPPLICATION_H
#define FDCORE_ABSTRACTAPPLICATION_H

#include <FDCore/Common/Object.h>
#include <FDCore/PluginManagement/AbstractPlugin.h>

namespace FDCore
{
    class AbstractApplication : Object
    {
      public:
        enum ExitStatus
        {
            ExitSuccess = 0,
            ExitFailure = -1
        };

      public:
        AbstractApplication() {}
        virtual ~AbstractApplication() = default;

        virtual bool init() = 0;
        virtual void quit() = 0;
        virtual int run(int argc, char **argv) = 0;

        virtual void addPlugin(AbstractPlugin *) {};
    };
} // namespace FDCore

#endif // FDCORE_ABSTRACTAPPLICATION_H