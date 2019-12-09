#ifndef ASSOCIATIVECONTAINER_H
#define ASSOCIATIVECONTAINER_H

#include <functional>
#include <optional>
#include <vector>

#include <FDCore/ComparableTrait.h>

namespace FDCore
{
    template<typename Key, typename Hash = std::hash<Key>>
    struct KeyType : public ComparableTrait<KeyType<Key, Hash>>
    {
        size_t hash;
        #ifdef DEBUG
        Key key
        #endif

        KeyType(const Key &k, const Hash &h) :
            hash(h(k))
            #ifdef DEBUG
            , key(k)
            #endif
        {}

        int64_t compare(const KeyType &other) { return hash - other.hash; }
    };

    template<typename Key, typename T, class Hash = std::hash<Key>>
    struct KeyValueType : public ComparableTrait<KeyValueType<Key, T, Hash>>,
                          public ComparableTrait<KeyType<Key, Hash>>
    {
        KeyType<Key, Hash> key;
        T value;

        KeyValueType(Key &&k, T &&value, const Hash &h):
            key(std::move(k), h),
            value(std::move(value))
        {}

        KeyValueType(const Key &k, const T &value, const Hash &h):
            key(k, h),
            value(value)
        {}

        int64_t compare(const KeyType<Key, Hash> &key) { return key.compare(key); }
        int64_t compare(const KeyValueType &other) { return compare(other.key); }
    };

    template<class Key, class T, class Hash = std::hash<Key>,
             class Allocator = std::allocator<KeyValueType<Key, T, Hash>>>
    class AssociativeContainer
    {
        public:
            typedef Key key_type;
            typedef T value_type;
            typedef KeyType<Key, Hash> cell_key_type;
            typedef KeyValueType<Key, T, Hash> cell_type;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef Hash hasher;
            typedef Allocator allocator_type;
            typedef cell_type& reference;
            typedef const cell_type& const_reference;
            typedef cell_type* pointer;
            typedef const cell_type* const_pointer;
            typedef std::vector<cell_type, allocator_type> container_type;
            typedef typename container_type::iterator iterator;
            typedef typename container_type::const_iterator const_iterator;
            typedef typename container_type::reverse_iterator reverse_iterator;
            typedef typename container_type::const_reverse_iterator const_reverse_iterator;

        protected:
            container_type m_container;
            hasher m_hash;

        public:
            iterator find(const key_type &k)
            {
                return std::lower_bound(begin(), end(), KeyType{ k, m_hash });
            }

            const_iterator find(const key_type &k) const
            {
                return std::lower_bound(begin(), end(), KeyType{ k, m_hash });
            }

            template<typename Predicate>
            iterator find_if(Predicate pred)
            {
                return std::find_if(begin(), end(), pred);
            }

            template<typename Predicate>
            const_iterator find_if(Predicate pred) const
            {
                return std::find_if(begin(), end(), pred);
            }

            template<typename Predicate>
            std::vector<iterator> find_all_if(Predicate pred)
            {
                std::vector<iterator> result;
                auto it = begin();
                auto last = end();
                while((it = std::find_if(it, last, pred)) != last)
                    result.push_back(it);

                return result;
            }

            bool contains(const key_type &k) const
            {
                return find(k) != end();
            }

            allocator_type get_allocator() const { return m_container.get_allocator(); }
            hasher hash_function() const { return m_hash; }

            iterator begin() { return m_container.begin(); }
            const_iterator begin() const { return m_container.begin(); }
            const_iterator cbegin() const { return m_container.cbegin(); }

            iterator end() { return m_container.end(); }
            const_iterator end() const { return m_container.end(); }
            const_iterator cend() const { return m_container.cend(); }

            reverse_iterator rbegin() { return m_container.rbegin(); }
            const_reverse_iterator rbegin() const { return m_container.rbegin(); }
            const_reverse_iterator crbegin() const { return m_container.crbegin(); }

            reverse_iterator rend() { return m_container.rend(); }
            const_reverse_iterator rend() const { return m_container.rend(); }
            const_reverse_iterator crend() const { return m_container.crend(); }

            pointer data() { return m_container.data(); }
            const_pointer data() const { return m_container.data(); }

            bool empty() const { return m_container.empty(); }
            size_type size() const { return m_container.size(); }
            size_type max_size() const { return m_container.max_size(); }
            size_type capacity() const { return m_container.capacity(); }

            void reserve(size_t size) { m_container.reserve(size); }
            void shrink_to_fit() { m_container.shrink_to_fit(); }

            void clear() { m_container.clear(); }

            iterator insert(const key_type &k, const value_type &value)
            {
                cell_type cell(k, value, m_hash);
                iterator it = std::lower_bound(m_container.begin(), m_container.end(), cell);
                m_container.insert(it, std::move(cell));
            }

            iterator insert(key_type &&k, value_type &&value)
            {
                cell_type cell(std::move(k), std::move(value), m_hash);
                iterator it = std::lower_bound(m_container.begin(), m_container.end(), cell);
                return m_container.insert(it, std::move(cell));
            }

            iterator erase(const key_type &k)
            {
                return m_container.erase(find(k));
            }

            template<typename Predicate>
            iterator erase_if(Predicate pred)
            {
                return m_container.erase(find_if(pred));
            }

            size_type count(const key_type &k) const
            {
                return std::count(begin(), end(), KeyType{ k, m_hash });
            }

            template<typename Predicate>
            size_type count_if(Predicate pred) const
            {
                return std::count_if(begin(), end(), pred);
            }

            void swap(AssociativeContainer &other) { m_container.swap(other); }

            std::optional<reference> at(const key_type &k)
            {
                iterator it = find(k);
                if(it == end())
                    return std::nullopt;

                return std::optional<reference>{ *it };
            }

            std::optional<const_reference> at(const key_type &k) const
            {
                const_iterator it = find(k);
                if(it == end())
                    return std::nullopt;

                return std::optional<const_reference>{ *it };
            }

            std::optional<reference> operator[](const key_type &k)
            {
                return at(k);
            }

            std::optional<const_reference> operator[](const key_type &k) const
            {
                return at(k);
            }
    };
}

#endif // ASSOCIATIVECONTAINER_H
