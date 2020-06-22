#ifndef FDCORE_LOGLEVEL_H
#define FDCORE_LOGLEVEL_H

#include <cstdint>
#include <string_view>

namespace FDCore
{
    enum LogLevel : uint8_t
    {
        Invalid = 255,
        Trace = 0,
        Debug = 1,
        Information = 2,
        Warning = 3,
        Error = 4,
        Fatal = 5
    };

    inline constexpr const char *logLevelToString(LogLevel level)
    {
        switch(level)
        {
            case Trace:
                return "Trace";

            case Debug:
                return "Debug";

            case Information:
                return "Information";

            case Warning:
                return "Warning";

            case Error:
                return "Error";

            case Fatal:
                return "Fatal";

            default:
                return "Invalid";
        }
    }

    inline LogLevel logLevelFromString(std::string_view str)
    {
        if(str == "Trace")
            return Trace;

        if(str == "Debug")
            return Debug;

        if(str == "Information")
            return Information;

        if(str == "Warning")
            return Warning;

        if(str == "Error")
            return Error;

        if(str == "Fatal")
            return Fatal;

        return Invalid;
    }

} // namespace FDCore

#endif // FDCORE_LOGLEVEL_H