#ifndef FDCORE_SHAREDRESOURCE_H
#define FDCORE_SHAREDRESOURCE_H

#include "CRTPTrait.h"

#include <type_traits>

#include "HasMemberTrait.h"

createMemberChecker(internal_delete)


namespace FDCore
{
	namespace internal
	{
		template<typename T>
		struct has_internal_delete
		{
			static const bool value = false;
		};
	}

	template<typename Derived, typename _ResourceType, typename _CounterType = uint32_t>
	class SharedResource : public CRTPTrait<Derived>
	{
		public:

			typedef _CounterType counter_type;
			typedef _ResourceType resource_type;

		protected:

			counter_type *m_count;
			resource_type *m_resource;

		public:

			SharedResource() : m_count(nullptr), m_resource(nullptr) {}

			explicit SharedResource(const resource_type &resource) : m_count(new counter_type), m_resource(new resource_type)
			{
				*m_count = 1;
				*m_resource = resource;
			}

			explicit SharedResource(const Derived &resource) :
				m_count(resource.m_count), m_resource(resource.m_resource)
			{
				if (resource)
					++(*m_count);
			}

			Derived &operator=(const Derived &resource)
			{
				this->reset(resource);

				return toDerivedRef();
			}

			Derived &operator=(const resource_type &resource)
			{
				this->reset(resource);
				return toDerivedRef();
			}

			~SharedResource()
			{
				this->destroy();

				onDelete<std::is_base_of<std::true_type, FDCore::has_internal_delete<Derived, void>>::value>();
			}

			void reset()
			{
				this->destroy();
			}

			void reset(const resource_type &resource)
			{
				this->destroy();
				m_count = new counter_type;
				m_resource = new resource_type;
				*m_resource = resource;
				*m_count = 1;
			}


			void reset(const Derived &resource)
			{
				this->destroy();
				m_count = resource.m_count;
				m_resource = resource.m_resource;
				++(*m_count);
			}

			void destroy()
			{
				if (m_resource != nullptr)
				{
					--(*m_count);
					if (*m_count == 0)
					{
						static_cast<Derived*>(this)->internal_destroy();
						delete m_resource;
						delete m_count;
					}
				}

				m_resource = nullptr;
				m_count = nullptr;
			}

			template<bool>
			void onDelete()
			{
			}

			template<>
			void onDelete<true>()
			{
				toDerived()->internal_delete();
			}

			operator bool() const { return m_count != nullptr && m_resource != nullptr; }
			operator const resource_type&() const { return *m_resource; }
			operator resource_type&() { return *m_resource; }

			resource_type &operator*() { return *m_resource; }
			resource_type *operator->() { return m_resource; }
			const resource_type &operator*() const { return *m_resource; }
			const resource_type *operator->() const { return m_resource; }
			resource_type *get() { return m_resource; }
			const resource_type *get() const { return m_resource; }
	};
}

#endif // FDCORE_SHAREDRESOURCE_H
