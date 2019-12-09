#ifndef COMPARABLETRAIT_H
#define COMPARABLETRAIT_H

namespace FDCore
{
    template<typename Derived, typename Comparable = Derived>
    class EqualTrait
    {
        bool operator!=(const Comparable &other) const
        {
            return !(static_cast<Derived&>(*this) == other);
        }
    };

    template<typename Comparable>
    class ComparableTrait : EqualTrait<ComparableTrait<Comparable>, Comparable>
    {
        public:
            bool operator==(const Comparable &other) const
            {
                return static_cast<Comparable*>(this)->compare(other) == 0;
            }

            bool operator<(const Comparable &other) const
            {
                return static_cast<Comparable*>(this)->compare(other) < 0;
            }

            bool operator<=(const Comparable &other) const
            {
                return !operator>(other);
            }

            bool operator>(const Comparable &other) const
            {
                return static_cast<Comparable*>(this)->compare(other) > 0;
            }

            bool operator>=(const Comparable &other) const
            {
                return !operator<(other);
            }
    };
}

#endif // COMPARABLETRAIT_H
