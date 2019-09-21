#ifndef FDCORE_PBCTRAIT_H
#define FDCORE_PBCTRAIT_H

namespace FDCore
{
	template<typename Parent>
	struct PBCTrait
	{
		typedef Parent parent_type;

		parent_type *toParent()
		{
			return static_cast<parent_type*>(this);
		}

		const parent_type *toParent() const
		{
			return static_cast<const parent_type*>(this);
		}

		parent_type &toParentRef()
		{
			return static_cast<parent_type &>(*this);
		}

		const parent_type &toParentRef() const
		{
			return static_cast<const parent_type &>(*this);
		}
	};
}

#endif // FDCORE_PBCTRAIT_H