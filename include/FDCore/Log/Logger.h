#ifndef FDCORE_LOGGER_H
#define FDCORE_LOGGER_H

#include <FDCore/Log/AbstractLogger.h>

namespace FDCore
{
    class Logger final : public AbstractLogger
    {
      public:
        using AbstractLogger::AbstractLogger;
        ~Logger() override = default;

        void log(LogLevel lvl, std::string_view text) override;
    };
} // namespace FDCore

#endif // FDCORE_LOGGER_H