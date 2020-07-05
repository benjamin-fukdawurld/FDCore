#ifndef FDCORE_TEST_TESTPLUGINAPI_H
#define FDCORE_TEST_TESTPLUGINAPI_H

#include <FDCore/Common/Macros.h>
#include <string>

namespace FDCore
{
    class FD_EXPORT PluginApi
    {
      public:
        int i;
        float pi;
        bool b;
        char c;
        std::string str;

      public:
        PluginApi() : i(42), pi(3.14159f), b(true), c('c'), str("string") {}
        virtual ~PluginApi() = default;

        virtual int f_i() = 0;
        virtual float f_f() = 0;
        virtual bool f_b() = 0;
        virtual char f_c() = 0;
        virtual std::string f_str() = 0;
    };
} // namespace FDCore

#endif // FDCORE_TEST_TESTPLUGINAPI_H