#ifndef FDCORE_ABSTRACTAPPLICATION_H
#define FDCORE_ABSTRACTAPPLICATION_H

#include <FDCore/Common/Object.h>
#include <FDCore/PluginManagement/AbstractPlugin.h>

namespace FDCore
{
    class AbstractApplication : public Object
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

        virtual std::vector<const char *> getTypeCodeHierarchy() const;

        virtual std::vector<size_t> getTypeCodeHashHierarchy() const;

        virtual const char *getTypeCode() const;

        virtual size_t getTypeCodeHash() const;

        virtual bool matchTypeCodeHash(size_t hash) const;
    };
} // namespace FDCore

generateTypeCode(FDCore::AbstractApplication);

#endif // FDCORE_ABSTRACTAPPLICATION_H