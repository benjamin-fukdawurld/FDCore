#include <FDCore/ThreadPool.h>

FDCore::ThreadPool::ThreadPool() : ThreadPool(std::thread::hardware_concurrency()) {}

FDCore::ThreadPool::ThreadPool(size_t nbThread) : m_run(true)
{
    m_threads.reserve(nbThread);
    for(size_t i = 0; i < nbThread; ++i)
        addThread();
}

FDCore::ThreadPool::~ThreadPool()
{
    m_run = false;
    m_cond.notify_all();

    for(size_t i = 0, imax = m_threads.size(); i < imax; ++i)
        m_threads[i].second.join();
}

size_t FDCore::ThreadPool::getNumberOfThreads() const { return m_threads.size(); }

void FDCore::ThreadPool::setNumberOfThreads(size_t nbThreads)
{
    if(nbThreads == m_threads.size())
        return;

    if(nbThreads < m_threads.size())
    {
        removeThreads(m_threads.size() - nbThreads);
        return;
    }

    for(size_t i = m_threads.size(); i < nbThreads; ++i)
        addThread();
}

void FDCore::ThreadPool::addThread()
{
    m_threads.push_back(
      std::make_pair(true, std::thread(&ThreadPool::workFunction, this, m_threads.size())));
}

void FDCore::ThreadPool::removeThreads(size_t nbThread)
{
    for(size_t i = m_threads.size() - 1, imax = i - nbThread; i > imax; --i)
        m_threads[i].first = false;

    m_cond.notify_all();

    for(size_t i = m_threads.size() - 1, imax = i - nbThread; i > imax; --i)
        m_threads[i].second.join();

    auto begin = m_threads.begin();
    std::advance(begin, m_threads.size() - nbThread);

    m_threads.erase(begin, m_threads.end());
}

void FDCore::ThreadPool::workFunction(size_t threadIndex)
{
    while(m_run && m_threads[threadIndex].first)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cond.wait(lock, [this, threadIndex] {
                return !m_run || !m_threads[threadIndex].first || !m_queue.empty();
            });

            if(!m_run || !m_threads[threadIndex].first)
                return;

            if(m_queue.empty())
                continue;

            task = std::move(m_queue.front());
            m_queue.pop();
        }

        task();
    }
}
