#ifndef FDCORE_ABSTRACTPLUGIN_H
#define FDCORE_ABSTRACTPLUGIN_H

#include <FDCore/ResourceManagement/AbstractResource.h>

namespace FDCore
{
    class AbstractPlugin : public AbstractResource
    {
      public:
        AbstractPlugin() = default;
        ~AbstractPlugin() override = default;

        virtual std::string getName() = 0;
    };
} // namespace FDCore

#endif // FDCORE_ABSTRACTPLUGIN_H