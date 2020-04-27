#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <future>
#include <cassert>

#include <FDCore/Macros.h>

namespace FDCore
{
    class FD_EXPORT ThreadPool
    {
        private:
            std::vector<std::pair<bool, std::thread>> m_threads;
            std::queue<std::function<void()>> m_queue;
            std::mutex m_mutex;
            std::condition_variable m_cond;
            bool m_run;

        public:
            ThreadPool();
            ThreadPool(size_t nbThread);
            ~ThreadPool();

            template<typename F, typename ...Args>
            std::future<typename std::result_of<F(Args...)>::type> enqueue(F&& f, Args&&... args);

            size_t getNumberOfThreads() const;
            void setNumberOfThreads(size_t nbThreads);

        private:
            void addThread();
            void removeThreads(size_t nbThread);

            void workFunction(size_t threadIndex);
    };

    template<typename F, typename ...Args>
    std::future<typename std::result_of<F(Args...)>::type> ThreadPool::enqueue(F&& f, Args&&... args)
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared< std::packaged_task<return_type()> >(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            // don't allow enqueueing after stopping the pool
            assert(m_run);

            m_queue.emplace([task](){ (*task)(); });
        }

        m_cond.notify_one();
        return res;
    }
}
#endif // THREADPOOL_H
