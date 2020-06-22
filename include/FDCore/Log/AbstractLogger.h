#ifndef FDCORE_ABSTRACTLOGGER_H
#define FDCORE_ABSTRACTLOGGER_H

#include <FDCore/Log/LogLevel.h>
#include <sstream>

namespace FDCore
{
    class AbstractLogger;

    class LoggerProxy
    {
      private:
        AbstractLogger &m_logger;
        std::ostringstream m_text;
        LogLevel m_level;

      public:
        LoggerProxy(AbstractLogger &logger, LogLevel lvl) : m_logger(logger), m_level(lvl) {}
        ~LoggerProxy();

        template<typename T>
        LoggerProxy &operator<<(const T &msg)
        {
            m_text << msg;
            return *this;
        }
    };

    class AbstractLogger
    {
      protected:
        uint8_t m_logThreshold;

      public:
        AbstractLogger(uint8_t logThreshold = 0) : m_logThreshold(logThreshold) {}
        virtual ~AbstractLogger() = default;

        virtual void log(LogLevel lvl, std::string_view text) = 0;

        LoggerProxy operator()(LogLevel lvl) { return LoggerProxy(*this, lvl); }
    };

    inline LoggerProxy::~LoggerProxy() { m_logger.log(m_level, m_text.str()); }
} // namespace FDCore

#endif // FDCORE_ABSTRACTLOGGER_H