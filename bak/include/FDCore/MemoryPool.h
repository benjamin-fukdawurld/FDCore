#ifndef FDCORE_MEMORYPOOL_H
#define FDCORE_MEMORYPOOL_H

#include "FDCore.h"
#include "MemoryBlock.h"

#include <vector>


namespace FDCore
{
    template<typename T>
    class Handle;


    class MemoryPool
    {
      protected:
        std::vector<MemoryBlock> m_blocks;
        std::vector<handle_ptr> m_handleTable;

        size_t m_poolSize;
        size_t m_used;

        uint8_t *m_pool;

      public:
        MemoryPool(size_t poolSize);
        ~MemoryPool() { delete[] m_pool; }


        size_t used() const { return m_used; }
        size_t capacity() const { return m_poolSize; }

        bool isFull() const { return m_used >= m_poolSize; }
        float fillRate() const { return static_cast<float>(m_used) / m_poolSize; }


        void compact();

        static void swap(handle_ptr a, handle_ptr b, size_t size);


        template<typename T>
        T *get(handle_ptr ptr)
        {
            auto it = std::find_if(m_blocks.begin(), m_blocks.end(),
                                   [&ptr](const MemoryBlock &cur) { return cur.getPtr() == ptr; });

            if(it != m_blocks.end())
                return it->get<T>();

            return nullptr;
        }

        size_t findEmptyBlock(size_t size) const { return findEmptyBlock(0, size); }

        size_t findEmptyBlock(size_t from, size_t size) const;

        template<typename T, typename... Args>
        Handle<T> allocate(Args... args)
        {
            return allocateFrom<T, Args...>(0, args...);
        }

        template<typename T, typename... Args>
        Handle<T> allocateFrom(size_t from, Args... args)
        {


            handle_ptr ptr = m_pool + findEmptyBlock(from, sizeof(T));
            m_handleTable.emplace_back(ptr);
            internal_allocate<T, Args...>(ptr, args...);
            return Handle<T>(m_handleTable.back(), *this);
        }


      private:
        template<typename T, typename... Args>
        T *internal_allocate(handle_ptr position, Args... args)
        {
            auto it = m_blocks.emplace(
              std::lower_bound(m_blocks.begin(), m_blocks.end(), [&position](const MemoryBlock &b) {
                  return position < b.getPtr();
              }));
            --it;

            m_blocks.emplace(it, MemoryBlock(position, sizeof(T), 0));

            T *tmp = new(position) T(args...);

            return tmp;
        }

        template<typename T, typename... Args>
        T *internal_allocateAligned(handle_ptr position, size_t alignment, Args... args)
        {
            auto it = m_blocks.emplace(
              std::lower_bound(m_blocks.begin(), m_blocks.end(), [&position](const MemoryBlock &b) {
                  return position < b.getPtr();
              }));
            --it;

            m_blocks.emplace(it, MemoryBlock(position, sizeof(T) + (alignment - 1), alignment));

            T *tmp = new(position) T(args...);

            return tmp;
        }

        template<typename T>
        void internal_destroy(T *obj)
        {
            obj->~T();
            FDCore::remove_if(m_blocks.begin(), m_blocks.end(),
                              [obj](const MemoryBlock &b) { return b.isInBlock(obj); });
        }

        size_t findEmptyBlockFromEnd(size_t end) const;

        void adjustHandles(size_t end, size_t offset);

        size_t getPoolEnd() const;
    };

} // namespace FDCore



#endif // FDCORE_MEMORYPOOL_H