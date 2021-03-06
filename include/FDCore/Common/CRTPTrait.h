#ifndef FDCORE_CRTPTRAIT_H
#define FDCORE_CRTPTRAIT_H

namespace FDCore
{
    /**
     * @brief CRTPTrait is an a CRTP helper class that provide an accesser to the derived type
     * This class is meant to be used when you you have a CRTP class. Your class will be declared as
     * following
     *
     * template<typename Derived>
     * class MyClass: public CRTPTrait<Derived>
     * {
     *  ...
     * };
     *
     * Then whenever you need to cast this object to its derived type you just need to call
     * CRTPTrait::asDerived()
     *
     * @tparam Derived The tuype deriving from CRTP trait
     */
    template<typename Derived>
    class CRTPTrait
    {
      protected:
        /**
         * @brief Returns a reference to this object as the Derived type; its equivalent to
         * reinterpret_cast<Derived&>(*this)
         *
         * @return a reference to this object a Derived&
         */
        Derived &asDerived() { return reinterpret_cast<Derived &>(*this); }

        /**
         * @brief Returns a const reference to this object as the Derived type; its equivalent to
         * reinterpret_cast<const Derived&>(*this)
         *
         * @return a reference to this object a const Derived&
         */
        const Derived &asDerived() const { return reinterpret_cast<const Derived &>(*this); }
    };

} // namespace FDCore

#endif // FDCORE_CRTPTRAIT_H
