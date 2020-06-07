#ifndef FDCORE_CRTPTRAIT_H
#define FDCORE_CRTPTRAIT_H

namespace FDCore
{
    template<typename Derived>
    struct CRTPTrait
    {
        typedef Derived derived_type;

        derived_type *toDerived() { return static_cast<derived_type *>(this); }

        const derived_type *toDerived() const { return static_cast<const derived_type *>(this); }

        derived_type &toDerivedRef() { return static_cast<derived_type &>(*this); }

        const derived_type &toDerivedRef() const
        {
            return static_cast<const derived_type &>(*this);
        }
    };
} // namespace FDCore

#endif // FDCORE_CRTPTRAIT_H
