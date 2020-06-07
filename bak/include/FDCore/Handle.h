#ifndef FDCORE_HANDLE_H
#define FDCORE_HANDLE_H

#include "FDCore.h"
#include "MemoryPool.h"

namespace FDCore
{
    template<typename T>
    class Handle
    {
        friend class MemoryPool;

      public:
        typedef T value_type;

      protected:
        handle_ptr &m_ptr;
        MemoryPool &m_pool;

        Handle(handle_ptr &ptr, MemoryPool &pool) : m_ptr(ptr), m_pool(pool) {}

      public:
        Handle(const Handle<T> &h) : m_ptr(h.m_ptr), m_pool(h.m_pool) {}

        Handle &operator=(const Handle<T> &h)
        {
            m_ptr = h.m_ptr;
            m_pool = h.m_pool;
            return *this;
        }

        static size_t size() { return sizeof(value_type); }

        handle_ptr getPtr() const { return m_ptr; }

        T *get() { return m_pool.get<T>(m_ptr); }

        T *operator->() { return m_pool.get<T>(m_ptr); }
        T &operator*() { return *(m_pool.get<T>(m_ptr)); }
    };
} // namespace FDCore



#endif // FDCORE_HANDLE_H