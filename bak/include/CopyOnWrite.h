#ifndef COPYONWRITE_H
#define COPYONWRITE_H

#include <memory>

namespace FDCore
{
    template<typename T>
    class CopyOnWrite
    {
      public:
        typedef std::shared_ptr<T> PointerType;

      private:
        PointerType m_ptr;

        void detach()
        {
            T *tmp = m_ptr.get();
            if(tmp != nullptr && !m_ptr.unique())
                m_ptr = PointerType(new T(*tmp));
        }

      public:
        constexpr CopyOnWrite() {}

        constexpr CopyOnWrite(std::nullptr_t t) : m_ptr(t) {}

        template<typename Y>
        explicit CopyOnWrite(Y *ptr) : m_ptr(ptr)
        {
        }

        template<typename Y, class Deleter>
        CopyOnWrite(Y *ptr, Deleter d) : m_ptr(ptr, d)
        {
        }

        template<typename Y, class Deleter, class Alloc>
        CopyOnWrite(Y *ptr, Deleter d, Alloc alloc) : m_ptr(ptr, d, alloc)
        {
        }

        CopyOnWrite(const std::shared_ptr<T> &refptr) : m_ptr(refptr) {}

        template<typename Deleter>
        CopyOnWrite(std::nullptr_t t, Deleter d) : m_ptr(t, d)
        {
        }

        template<typename Deleter, class Alloc>
        CopyOnWrite(std::nullptr_t t, Deleter d, Alloc alloc) : m_ptr(t, d, alloc)
        {
        }

        template<typename Y>
        CopyOnWrite(const std::shared_ptr<Y> &r, T *ptr) : m_ptr(r, ptr)
        {
        }

        template<typename Y>
        CopyOnWrite(const std::shared_ptr<Y> &r) : m_ptr(r)
        {
        }


        CopyOnWrite(std::shared_ptr<T> &&r) : m_ptr(std::move(r)) {}

        template<typename Y>
        CopyOnWrite(std::shared_ptr<Y> &&r) : m_ptr(std::move(r))
        {
        }

        template<typename Y>
        explicit CopyOnWrite(const std::weak_ptr<Y> &r) : m_ptr(r)
        {
        }

        template<typename Y>
        CopyOnWrite(std::auto_ptr<Y> &&r) : m_ptr(r)
        {
        }


        template<typename Y, class Deleter>
        CopyOnWrite(std::unique_ptr<Y, Deleter> &&r) : m_ptr(r)
        {
        }

        void reset() noexcept { m_ptr.reset(); }

        template<typename Y>
        void reset(Y *ptr)
        {
            m_ptr.reset(ptr);
        }


        template<typename Y, class Deleter>
        void reset(Y *ptr, Deleter d)
        {
            m_ptr.reset(ptr, d);
        }

        template<typename Y, class Deleter, class Alloc>
        void reset(Y *ptr, Deleter d, Alloc alloc)
        {
            m_ptr.reset(ptr, d, alloc);
        }

        void swap(std::shared_ptr<T> &r) noexcept { m_ptr.swap(r); }

        void swap(CopyOnWrite<T> &r) noexcept { m_ptr.swap(r.m_ptr); }

        T *get() const noexcept { return m_ptr.get(); }

        const T &operator*() const { return *m_ptr; }

        T &operator*()
        {
            detach();
            return *m_ptr;
        }

        const T *operator->() const { return m_ptr.operator->(); }

        T *operator->()
        {
            detach();
            return m_ptr.operator->();
        }

        explicit operator bool() const noexcept { return static_cast<bool>(m_ptr); }

        long use_count() const noexcept { return m_ptr.use_count(); }
    };
} // namespace FDCore

#endif // COPYONWRITE_H
