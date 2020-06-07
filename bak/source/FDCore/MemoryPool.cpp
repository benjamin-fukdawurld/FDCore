#include "MemoryPool.h"

using namespace FDCore;


MemoryPool::MemoryPool(size_t poolSize) :
    m_poolSize(poolSize),
    m_used(0),
    m_pool(new uint8_t[poolSize]())
{
    m_handleTable.reserve(poolSize / 8);
    m_blocks.reserve(poolSize / 8);
    memset(m_pool, 0, poolSize);
}

void MemoryPool::compact()
{
    size_t poolEnd = getPoolEnd();
    size_t oldEnd = poolEnd;

    for(size_t i = poolEnd; i > 0; --i)
    {
        size_t end = i - 1;
        if(m_pool[end] != 0)
            continue;

        size_t start = findEmptyBlockFromEnd(end);
        size_t size = end - start;

        memmove(m_pool + start, m_pool + end, poolEnd - start);
        poolEnd -= size;
        i = start;

        adjustHandles(end, end - start);
    }

    memset(m_pool + poolEnd, 0, oldEnd - poolEnd);
}

void MemoryPool::swap(handle_ptr a, handle_ptr b, size_t size)
{
    uint64_t tmp64;
    while(size > 8)
    {
        memcpy(&tmp64, a, 8);
        memcpy(a, b, 8);
        memcpy(b, &tmp64, 8);

        a += 8;
        b += 8;
        size -= 8;
    }

    uint8_t tmp8;
    while(size > 0)
    {
        tmp8 = *a;
        *a = *b;
        *b = tmp8;

        ++a;
        ++b;
        --size;
    }
}


size_t MemoryPool::findEmptyBlock(size_t from, size_t size) const
{
    for(size_t i = 0; i < m_blocks.size(); ++i)
    {
        size_t distance = std::distance(m_pool + from, m_blocks[i].getPtr());
        if(distance >= size)
            return from;

        from += m_blocks[i].size();
    }

    return from;
}


size_t MemoryPool::findEmptyBlockFromEnd(size_t end) const
{
    size_t start = end + 1;
    while(start > 0)
    {
        if(m_pool[start - 1] != 0)
            break;

        --start;
    }

    return start - 1;
}


void MemoryPool::adjustHandles(size_t end, size_t offset)
{
    handle_ptr handle_end = m_pool + end;
    for(size_t j = 0, jmax = m_handleTable.size(); j < jmax; ++j)
    {
        if(m_handleTable[j] < handle_end)
            continue;

        m_handleTable[j] = (m_handleTable[j] - offset);
    }
}



size_t MemoryPool::getPoolEnd() const
{
    if(m_blocks.empty())
        return 0;

    return std::distance(m_pool, m_blocks.back().getPtr()) + m_blocks.back().size();
}
