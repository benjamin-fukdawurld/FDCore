#ifndef FDCORE_IDENTIFIABLE_H
#define FDCORE_IDENTIFIABLE_H

#include <FDCore/Common/Comparison.h>

namespace FDCore
{
    template<typename T>
    struct id_generator
    {
      public:
        static constexpr const T no_id { 0 };

      private:
        static T nextId;

      public:
        template<typename IdentifiableType>
        T operator()(const IdentifiableType &)
        {
            return ++nextId;
        }
    };

    template<typename T>
    T id_generator<T>::nextId(id_generator<T>::no_id);

    template<>
    struct id_generator<uintptr_t>
    {
      public:
        static constexpr const uintptr_t no_id { 0 };

      public:
        template<typename IdentifiableType>
        uintptr_t operator()(const IdentifiableType &identifiable)
        {
            return reinterpret_cast<uintptr_t>(&identifiable);
        }
    };

    template<typename IdType,
             typename ComparisonType = IdType,
             typename Compare = comparer<IdType, ComparisonType>,
             typename IdGenerator = id_generator<IdType>>
    class Identifiable :
        public IComparable<Identifiable<IdType, ComparisonType, Compare>, ComparisonType>,
        public IComparable<IdType, ComparisonType>
    {
      public:
        typedef IdType id_type;
        typedef ComparisonType comparison_type;
        typedef Compare compare_type;
        typedef IdGenerator id_generator_type;
        typedef Identifiable<id_type, comparison_type, compare_type, id_generator_type>
          identifiable_type;

      protected:
        id_type m_id;
        compare_type m_comparer;

      public:
        Identifiable() : m_id(id_generator_type::no_id) { m_id = id_generator_type()(*this); }

        Identifiable(const identifiable_type &) = delete;

        Identifiable(identifiable_type &&) = default;

        Identifiable &operator=(const identifiable_type &) = delete;

        Identifiable &operator=(identifiable_type &&) = default;

        id_type getId() const { return m_id; }

        comparison_type compare(const identifiable_type &to_compare) const override
        {
            return m_comparer(m_id, to_compare.m_id);
        }

        comparison_type compare(const id_type &id) const override { return m_comparer(m_id, id); }
    };

    template<>
    class Identifiable<uintptr_t,
                       intptr_t,
                       FDCore::comparer<uintptr_t, intptr_t>,
                       FDCore::id_generator<uintptr_t>> :
        public IComparable<Identifiable<uintptr_t,
                                        intptr_t,
                                        FDCore::comparer<uintptr_t, intptr_t>,
                                        FDCore::id_generator<uintptr_t>>>,
        public IComparable<uintptr_t, intptr_t>
    {
      public:
        typedef uintptr_t id_type;
        typedef intptr_t comparison_type;
        typedef FDCore::comparer<uintptr_t, intptr_t> compare_type;
        typedef FDCore::id_generator<uintptr_t> id_generator_type;
        typedef Identifiable<id_type, comparison_type, compare_type, id_generator_type>
          identifiable_type;

      public:
        Identifiable() = default;

        Identifiable(const identifiable_type &) = delete;

        Identifiable(identifiable_type &&) = default;

        Identifiable &operator=(const identifiable_type &) = delete;

        Identifiable &operator=(identifiable_type &&) = default;

        id_type getId() const { return id_generator_type()(*this); }

        comparison_type compare(const identifiable_type &to_compare) const override
        {
            return compare_type()(getId(), to_compare.getId());
        }

        comparison_type compare(const id_type &id) const override
        {
            return compare_type()(getId(), id);
        }
    };
} // namespace FDCore

#endif // FDCORE_IDENTIFIABLE_H
