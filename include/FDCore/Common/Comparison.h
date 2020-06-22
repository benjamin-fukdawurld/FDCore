#ifndef FDCORE_COMPARISON_H
#define FDCORE_COMPARISON_H

#include <cstdint>

namespace FDCore
{
    template<typename T, typename ResultType = T>
    struct comparer
    {
        ResultType operator()(const T &a, const T &b) const
        {
            return static_cast<ResultType>(a) - static_cast<ResultType>(b);
        }
    };

    /**
     * @brief EqualTrait is a CRTP class that provide a != operator based on the == operator of it's
     * derived class
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
            return !(static_cast<Derived &>(*this) == other);
        }
    };

    template<typename T, typename ResultType = int64_t>
    class IComparable : public EqualTrait<IComparable<T, ResultType>, T>
    {
      public:
        virtual ResultType compare(const T &to_compare) const = 0;

        /**
         * @brief Checks if this object and other are equal based on the result of
         * this->compare(other)
         *
         * @param other the value to compare with this object
         * @return true if this->compare(other) == 0, false otherwise
         */
        bool operator==(const T &other) const { return compare(other) == 0; }

        /**
         * @brief Checks if this object is less than other based on the result of
         * this->compare(other)
         *
         * @param other the value to compare with this object
         * @return true if this->compare(other) < 0, false otherwise
         */
        bool operator<(const T &other) const { return compare(other) < 0; }

        /**
         * @brief Checks if this object is less or equals to other based on the result of
         * this->compare(other)
         *
         * @param other the value to compare with this object
         * @return true if this->compare(other) <= 0, false otherwise
         */
        bool operator<=(const T &other) const { return !operator>(other); }

        /**
         * @brief Checks if this object is greater than other based on the result of
         * this->compare(other)
         *
         * @param other the value to compare with this object
         * @return true if this->compare(other) > 0, false otherwise
         */
        bool operator>(const T &other) const { return compare(other) > 0; }

        /**
         * @brief Checks if this object is greater or equal to other based on the result of
         * this->compare(other)
         *
         * @param other the value to compare with this object
         * @return true if this->compare(other) >= 0, false otherwise
         */
        bool operator>=(const T &other) const { return !operator<(other); }
    };
} // namespace FDCore

#endif // FDCORE_COMPARISON_H