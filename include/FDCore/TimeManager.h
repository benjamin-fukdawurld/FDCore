#ifndef TIME_H
#define TIME_H

#include <chrono>
#include <cassert>

#include <FDCore/Macros.h>

namespace FDCore
{
    template<typename ClockType = std::chrono::steady_clock>
    class TimeManager
    {
        public:
            typedef ClockType clock_type;
            typedef std::chrono::time_point<clock_type> time_point;

        protected:
            time_point m_beginTime;
            time_point m_lastTime;

        public:
            TimeManager() {}

            template<typename Duration = std::chrono::milliseconds>
            typename Duration::rep getBeginTime() const
            {
                return std::chrono::duration_cast<Duration>(m_beginTime.time_since_epoch()).count();
            }

            template<typename Duration = std::chrono::milliseconds>
            typename Duration::rep getLastTime() const
            {
                return std::chrono::duration_cast<Duration>(m_lastTime.time_since_epoch()).count();
            }

            template<typename Duration = std::chrono::milliseconds>
            typename Duration::rep getCurrentTime() const
            {
                return getTime<Duration>();
            }

            template<typename Duration = std::chrono::milliseconds>
            typename Duration::rep getElapsedTime() const
            {
                auto time_point = clock_type::now() - m_beginTime;
                return std::chrono::duration_cast<Duration>(time_point).count();
            }

            template<typename Duration = std::chrono::milliseconds>
            typename Duration::rep getDeltaTime() const
            {
                auto time_point = clock_type::now() - m_lastTime;
                return std::chrono::duration_cast<Duration>(time_point).count();
            }

            bool hasBeginTime() const
            {
                return m_beginTime.time_since_epoch().count() != 0;
            }

            bool hasLastTime() const
            {
                return m_lastTime.time_since_epoch().count() != 0;
            }

            void start()
            {
                assert("TimeManager has already been started (use restart instead of start)"
                       && !hasBeginTime());

                m_lastTime = m_beginTime = clock_type::now();
            }

            void restart()
            {
                m_lastTime = m_beginTime = clock_type::now();
            }

            void recordTime()
            {
                m_lastTime = clock_type::now();
            }

            template<typename Duration = std::chrono::milliseconds>
            static typename Duration::rep getTime()
            {
                auto time_point = clock_type::now();
                return std::chrono::duration_cast<Duration>(time_point.time_since_epoch()).count();
            }
    };
}

#endif // TIME_H
