#ifndef FDCORE_MEMORYBLOCK_H
#define FDCORE_MEMORYBLOCK_H

#include "FDCore.h"

namespace FDCore
{
	class MemoryBlock
	{
		friend class MemoryPool;

		protected:

			size_t m_size;
			size_t m_align;
			handle_ptr m_ptr;

			MemoryBlock(handle_ptr ptr, size_t size, size_t align) : m_ptr(ptr), m_size(size), m_align(align) {}

			MemoryBlock(handle_ptr ptr, size_t size) : MemoryBlock(ptr, size, 0) {}

			MemoryBlock() : MemoryBlock(nullptr, 0, 0) {}

		public:

			template<typename T>
			T *get()
			{
				if(!m_align)
					return reinterpret_cast<T*>(m_ptr);

				return FDCore::alignMemory<T, handle_ptr>(m_ptr, m_align);
			}

			handle_ptr getPtr() const { return m_ptr; }

			size_t size() const { return m_size; }

			size_t alignment() const { return m_align; }


			template<typename T>
			bool isInBlock(T *ptr)
			{
				return reinterpret_cast<unsigned int>(ptr) >= reinterpret_cast<unsigned int>(m_ptr)
					&& reinterpret_cast<unsigned int>(ptr) < reinterpret_cast<unsigned int>(m_ptr) + m_size;
			}


			void align(size_t alignment) { m_align = alignment; }
	};

}



#endif // FDCORE_MEMORYBLOCK_H