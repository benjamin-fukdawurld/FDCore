#ifndef COMPARABLETRAIT_H
#define COMPARABLETRAIT_H

namespace FDCore
{
    /**
     * @brief EqualTrait is a CRTP class that provide a != operator based on the == operator of it's derived class
     *
     * @tparam Derived The type that derives from EqualTrait
     * @tparam Comparable the type that is comparable to this one
     */
    template<typename Derived, typename Comparable = Derived>
    class EqualTrait
    {
        /**
         * @brief compare that this object and other are not equals using the operator == of Derived
         *
         * @param other the value to compare with this object
         * @return the inverse of the operator == of Derived
         */
        bool operator!=(const Comparable &other) const
        {
            return !(static_cast<Derived&>(*this) == other);
        }
    };

    /**
     * @brief ComparableTrait is a CRTP class that implements all comparison operators based on the compare
     * method of the Comparable class. The compare method must return a value that is comparable with 0.
     * If the result of a.compare(b) is 0 then a == b is true otherwise if the result is < 0, a < b and if
     * the result is greater than 0 a > b
     *
     * @tparam Derived  The type that derives from ComparableTrait
     * @tparam Comparable the type that is comparable to this one
     */
    template<typename Derived, typename Comparable = Derived>
    class ComparableTrait : EqualTrait<ComparableTrait<Derived, Comparable>, Comparable>
    {
        public:

            /**
             * @brief Checks if this object and other are equal based on the result of this->compare(other)
             *
             * @param other the value to compare with this object
             * @return true if this->compare(other) == 0, false otherwise
             */
            bool operator==(const Comparable &other) const
            {
                return static_cast<const Derived*>(this)->compare(other) == 0;
            }

            /**
             * @brief Checks if this object is less than other based on the result of this->compare(other)
             *
             * @param other the value to compare with this object
             * @return true if this->compare(other) < 0, false otherwise
             */
            bool operator<(const Comparable &other) const
            {
                return static_cast<const Derived*>(this)->compare(other) < 0;
            }

            /**
             * @brief Checks if this object is less or equals to other based on the result of this->compare(other)
             *
             * @param other the value to compare with this object
             * @return true if this->compare(other) <= 0, false otherwise
             */
            bool operator<=(const Comparable &other) const
            {
                return !operator>(other);
            }

            /**
             * @brief Checks if this object is greater than other based on the result of this->compare(other)
             *
             * @param other the value to compare with this object
             * @return true if this->compare(other) > 0, false otherwise
             */
            bool operator>(const Comparable &other) const
            {
                return static_cast<const Derived*>(this)->compare(other) > 0;
            }

            /**
             * @brief Checks if this object is greater or equal to other based on the result of this->compare(other)
             *
             * @param other the value to compare with this object
             * @return true if this->compare(other) >= 0, false otherwise
             */
            bool operator>=(const Comparable &other) const
            {
                return !operator<(other);
            }
    };
}

#endif // COMPARABLETRAIT_H
