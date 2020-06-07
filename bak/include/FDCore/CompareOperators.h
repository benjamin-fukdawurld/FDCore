#pragma once


#ifndef ICOMPARABLE_H
    #define ICOMPARABLE_H


    #include <iostream>

namespace FDCore
{
    template<typename T>
    class CompareOperators
    {
      public:
        bool operator>=(const CompareOperators<T> &other) const
        {
            return !(static_cast<T *>(this)->operator<(other));
        }

        bool operator>(const CompareOperators<T> &other) const
        {
            return !(static_cast<T *>(this)->operator<=(other));
        }

        bool operator<=(const CompareOperators<T> &other) const
        {
            return !other.operator<(static_cast<T>(*this));
        }


        bool operator==(const CompareOperators<T> &other) const
        {
            return !(static_cast<T *>(this)->operator<(other)) &&
                   !(static_cast<T *>(this)->operator>(other));
        }

        bool operator!=(const CompareOperators<T> &other) const
        {
            return !(static_cast<T *>(this)->operator==(other));
        }
    };
} // namespace FDCore

#endif // ICOMPARABLE_H