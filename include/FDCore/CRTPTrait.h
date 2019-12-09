#ifndef CRTPTRAIT_H
#define CRTPTRAIT_H

namespace FDCore
{

    template<typename Derived>
    class CRTPTrait
    {
        protected:
            Derived &asDerived() { return static_cast<Derived&>(*this); }
            const Derived &asDerived() const { return static_cast<const Derived&>(*this); }
    };

}

#endif // CRTPTRAIT_H
