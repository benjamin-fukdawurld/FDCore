#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

#include <cstdint>

#include <FDCore/ComparableTrait.h>
#include <type_traits>
#include <utility>

namespace FDCore
{
    template<typename IdType>
    struct DefaultIdGenerator {};

    template<typename IdType>
    struct DefaultIdCompare {};

    template<>
    struct DefaultIdGenerator<uintptr_t>
    {
        template<typename T>
        static uintptr_t generate(const T *identifiable)
        {
            return reinterpret_cast<uintptr_t>(identifiable);
        }
    };

    template<>
    struct DefaultIdCompare<uintptr_t>
    {
        typedef std::ptrdiff_t comparison_type;

        static comparison_type compare(uintptr_t a, uintptr_t b)
        {
            return static_cast<comparison_type>(a) - static_cast<comparison_type>(b);
        }
    };

    template<typename IdType,
             typename IdGenerator = DefaultIdGenerator<IdType>,
             typename Compare = DefaultIdCompare<IdType>>
    class Identifiable : public ComparableTrait<IdType>,
            public ComparableTrait<Identifiable<IdType, IdGenerator, Compare>>
    {
        friend ComparableTrait<IdType>;

        public:
            typedef IdType id_type;
            typedef IdGenerator id_generator_type;
            typedef Compare compare_type;
            typedef typename Compare::comparison_type comparison_type;

        private:
            id_type m_id;

        public:
            Identifiable() : m_id(id_generator_type::generate(this))
            {}

            Identifiable(const Identifiable<id_type, id_generator_type, compare_type> &) : Identifiable()
            {}

            Identifiable(Identifiable<id_type, id_generator_type, compare_type> &&other) :
                m_id(std::move(other.m_id))
            {}

            id_type getId() const { return m_id; }

        private:
            comparison_type compare(const id_type &id) { return compare_type::compare(m_id, id); }
            comparison_type compare(const Identifiable<id_type, id_generator_type, compare_type> &other) { return compare(other.m_id); }
    };

    template<>
    class Identifiable<uintptr_t, DefaultIdGenerator<uintptr_t>, DefaultIdCompare<uintptr_t>>
            : public ComparableTrait<uintptr_t>,
              public ComparableTrait<Identifiable<uintptr_t,
                     DefaultIdGenerator<uintptr_t>,
                     DefaultIdCompare<uintptr_t>
                  >
              >
    {
        friend ComparableTrait<uintptr_t>;

        public:
            typedef uintptr_t id_type;
            typedef DefaultIdGenerator<uintptr_t> id_generator_type;
            typedef DefaultIdCompare<uintptr_t> compare_type;
            typedef compare_type::comparison_type comparison_type;

        public:
            Identifiable()
            {}

            Identifiable(const Identifiable<id_type, id_generator_type, compare_type> &) = default;

            Identifiable(Identifiable<id_type, id_generator_type, compare_type> &&) = default;

            Identifiable &operator=(const Identifiable<id_type, id_generator_type, compare_type> &) = default;

            Identifiable &operator=(Identifiable<id_type, id_generator_type, compare_type> &&) = default;

            id_type getId() const { return id_generator_type::generate(this); }

        private:
            comparison_type compare(const id_type &id) { return compare_type::compare(getId(), id); }
            comparison_type compare(const Identifiable &other) { return compare(other.getId()); }
    };
}

#endif // IDENTIFIABLE_H
