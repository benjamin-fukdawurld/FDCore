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

        comparison_type compare(uintptr_t a, uintptr_t b)
        {
            return static_cast<comparison_type>(a) - static_cast<comparison_type>(b);
        }
    };

    template<typename IdType = uintptr_t,
             typename IdGenerator = DefaultIdGenerator<IdType>,
             typename Compare = DefaultIdCompare<IdType>>
    class Identifiable : public ComparableTrait<IdType>,
            public ComparableTrait<Identifiable<IdType, IdGenerator, Compare>>
    {
        friend ComparableTrait<uintptr_t>;

        public:
            typedef IdType id_type;
            typedef typename Compare::comparison_type comparison_type;

        private:
            id_type m_id;

        public:
            Identifiable() : m_id(IdGenerator::generate(this))
            {}

            Identifiable(const Identifiable<IdType, IdGenerator, Compare> &) : Identifiable()
            {}

            Identifiable(const Identifiable<IdType, IdGenerator, Compare> &&other) :
                m_id(std::move(other.m_id))
            {}

            id_type getId() const { return m_id; }

        private:
            comparison_type compare(const id_type &id) { return Compare::compare(m_id, id); }
            comparison_type compare(const Identifiable &other) { return compare(other.m_id); }
    };
}

#endif // IDENTIFIABLE_H
