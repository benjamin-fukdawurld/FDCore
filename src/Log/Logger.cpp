#include <FDCore/Log/Logger.h>
#include <iostream>

void FDCore::Logger::log(LogLevel lvl, std::string_view text)
{
    std::clog << FDCore::logLevelToString(lvl) << ": " << text << std::endl;
}