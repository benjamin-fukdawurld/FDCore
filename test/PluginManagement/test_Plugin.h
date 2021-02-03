#ifndef FDCORE_TEST_TESTPLUGIN_H
#define FDCORE_TEST_TESTPLUGIN_H

#include "test_PluginApi.h"

namespace FDCore
{
    class FD_EXPORT Plugin : public PluginApi
    {
      public:
        Plugin() : PluginApi() {}
        virtual ~Plugin() = default;

        int f_i() override;
        float f_f() override;
        bool f_b() override;
        char f_c() override;
        std::string f_str() override;
    };

    extern "C" FD_EXPORT Plugin plugin;
    Plugin plugin;

} // namespace FDCore

#endif // FDCORE_TEST_TESTPLUGIN_H