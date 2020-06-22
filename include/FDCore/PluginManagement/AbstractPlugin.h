#ifndef FDCORE_ABSTRACTPLUGIN_H
#define FDCORE_ABSTRACTPLUGIN_H

#include <FDCore/AbstractResource.h>

namespace FDCore
{
    class AbstractPlugin : public AbstractResource
    {
      public:
        AbstractPlugin() = default;
        virtual ~AbstractPlugin() = default;

        void *getSymbol() = 0;
    };
} // namespace FDCore

#endif // FDCORE_ABSTRACTPLUGIN_H