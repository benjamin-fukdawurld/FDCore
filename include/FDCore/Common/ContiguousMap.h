#ifndef FDCORE_CONTIGUOUSMAP_H
#define FDCORE_CONTIGUOUSMAP_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>


namespace FDCore
{
    template<typename Key,
             typename T,
             typename Hash = std::hash<Key>,
             typename Equal = std::equal_to<Key>,
             typename Allocator = std::allocator<std::pair<Key, T>>>
    class ContiguousMap
    {
      public:
        typedef Key key_type;                   ///< the container key type
        typedef T value_type;                   ///< the container value type
        typedef key_type *key_type_pointer;     ///< a pointer to the container key type
        typedef value_type *value_type_pointer; ///< a pointer to the container value type
        typedef const key_type
          *const_key_type_pointer; ///< a constant pointer to the container key type
        typedef const value_type
          *const_value_type_pointer;          ///< a constant pointer to the container value type
        typedef key_type &key_type_reference; ///< a reference to the container key type
        typedef value_type &value_type_reference; ///< a reference to the container value type
        typedef const key_type
          &const_key_type_reference; ///< a constant reference to the container key type
        typedef const value_type
          &const_value_type_reference; ///< a constant reference to the container value type
        typedef size_t size_type;      ///< the container size type
        typedef ptrdiff_t
          difference_type;        ///< signed integer used to check distance between two cells
        typedef Hash hasher_type; ///< the container hasher type
        typedef Equal key_equal_type;
        typedef Allocator allocator_type;         ///< the container allocator type
        typedef std::pair<Key, T> cell_type;      ///< the container cell type
        typedef cell_type &reference;             ///< the container cell reference type
        typedef const cell_type &const_reference; ///< the container cell const reference type
        typedef cell_type *pointer;               ///< the container cell pointer type
        typedef const cell_type *const_pointer;   ///< the container cell const pointer type
        typedef std::vector<cell_type, allocator_type>
          container_type; ///< the container underlying containing structure reference type
        typedef typename container_type::iterator iterator; ///< the container iterator type
        typedef typename container_type::const_iterator
          const_iterator; ///< the container const iterator type
        typedef typename container_type::reverse_iterator
          reverse_iterator; ///< the container reverse iterator type
        typedef typename container_type::const_reverse_iterator
          const_reverse_iterator; ///< the container const reverse iterator type
        typedef ContiguousMap<key_type, value_type, hasher_type, key_equal_type, allocator_type>
          contiguous_map_type;

      protected:
        container_type m_container;
        hasher_type m_hasher;
        key_equal_type m_equal;

      public:
        explicit ContiguousMap(const Hash &hash = Hash(),
                               const key_equal_type &equal = key_equal_type(),
                               const Allocator &alloc = Allocator()) :
            m_container(alloc),
            m_hasher(hash),
            m_equal(equal)
        {
        }

        explicit ContiguousMap(std::initializer_list<cell_type> init,
                               const Hash &hash = Hash(),
                               const key_equal_type &equal = key_equal_type(),
                               const Allocator &alloc = Allocator()) :
            m_container(alloc),
            m_hasher(hash),
            m_equal(equal)
        {
            *this = init;
        }

        ContiguousMap(const ContiguousMap &m) = default;
        ContiguousMap(ContiguousMap &&m) = default;

        ContiguousMap &operator=(const ContiguousMap &m) = default;
        ContiguousMap &operator=(ContiguousMap &&m) = default;

        ContiguousMap &operator=(std::initializer_list<cell_type> l)
        {
            m_container = l;
            std::sort(m_container.begin(), m_container.end(),
                      [this](const cell_type &a, const cell_type &b) {
                          return m_hasher(a.first) < m_hasher(b.first);
                      });
        }

        /**
         * @brief Returns an hash value for a given key
         * @param key the key to hash
         * @return an hash value for a given key
         */
        size_t hashKey(key_type key) const { return m_hasher(key); }

        /**
         * @brief Get the allocator object
         *
         * @return the container's allocator
         */
        allocator_type get_allocator() const { return m_container.get_allocator(); }

        /**
         * @brief Returns the hasher
         *
         * @return the conainer's hasher
         */
        hasher_type hash_function() const { return m_hasher; }

        /**
         * @brief Returns an iterator to the beginning of the container
         *
         * @return An iterator to the beginning of the container
         */
        iterator begin() { return m_container.begin(); }

        /**
         * @brief Returns an iterator to the beginning of the container
         *
         * @return An iterator to the beginning of the container
         */
        const_iterator begin() const { return m_container.begin(); }

        /**
         * @brief Returns an iterator to the beginning of the container
         *
         * @return An iterator to the beginning of the container
         */
        const_iterator cbegin() const { return m_container.cbegin(); }

        /**
         * @brief Returns an iterator to the end of the container
         *
         * @return An iterator to the end of the container
         */
        iterator end() { return m_container.end(); }

        /**
         * @brief Returns an iterator to the end of the container
         *
         * @return An iterator to the end of the container
         */
        const_iterator end() const { return m_container.end(); }

        /**
         * @brief Returns an iterator to the end of the container
         *
         * @return An iterator to the end of the container
         */
        const_iterator cend() const { return m_container.cend(); }

        /**
         * @brief Returns a reverse iterator to the beginning of the container
         *
         * @return A reverse iterator to the beginning of the container
         */
        reverse_iterator rbegin() { return m_container.rbegin(); }

        /**
         * @brief Returns a reverse iterator to the beginning of the container
         *
         * @return A reverse iterator to the beginning of the container
         */
        const_reverse_iterator rbegin() const { return m_container.rbegin(); }

        /**
         * @brief Returns a reverse iterator to the beginning of the container
         *
         * @return A reverse iterator to the beginning of the container
         */
        const_reverse_iterator crbegin() const { return m_container.crbegin(); }

        /**
         * @brief Returns a reverse iterator to the end of the container
         *
         * @return A reverse iterator to the end of the container
         */
        reverse_iterator rend() { return m_container.rend(); }

        /**
         * @brief Returns a reverse iterator to the end of the container
         *
         * @return A reverse iterator to the end of the container
         */
        const_reverse_iterator rend() const { return m_container.rend(); }

        /**
         * @brief Returns a reverse iterator to the end of the container
         *
         * @return A reverse iterator to the end of the container
         */
        const_reverse_iterator crend() const { return m_container.crend(); }

        /**
         * @brief Returns a pointer to the first element of the container
         *
         * @return A pointer to the first element of the container
         */
        pointer data() { return m_container.data(); }

        /**
         * @brief Returns a pointer to the first element of the container
         *
         * @return A pointer to the first element of the container
         */
        const_pointer data() const { return m_container.data(); }

        /**
         * @brief Checks whether the container is empty or not
         *
         * @return true if the container is empty false otherwise
         */
        bool empty() const { return m_container.empty(); }

        /**
         * @brief Returns the number of elements
         *
         * @return the number of elements
         */
        size_type size() const { return m_container.size(); }

        /**
         * @brief Returns the maximum possible number of elements
         *
         * @return the maximum possible number of elements
         */
        size_type max_size() const { return m_container.max_size(); }

        /**
         * @brief Returns the number of elements that can be held in currently allocated storage
         *
         * @return the number of elements that can be held in currently allocated storage
         */
        size_type capacity() const { return m_container.capacity(); }

        /**
         * @brief Reserves storage, if size is less than or equal to the current size of the
         * container it does nothing
         *
         * @param size the number of element to reserve
         */
        void reserve(size_t size) { m_container.reserve(size); }

        /**
         * @brief Reduces memory usage by freeing unused memory
         *
         */
        void shrink_to_fit() { m_container.shrink_to_fit(); }

        /**
         * @brief Clears the content of the container
         *
         */
        void clear() { m_container.clear(); }

        bool contains(const key_type &key) { return binary_search(begin(), end(), key); }

        iterator insert(const key_type &key, const value_type &value)
        {
            size_t hash = m_hasher(key);
            auto low_it = lower_bound_impl(begin(), end(), hash, m_hasher);
            if(low_it == end())
                return m_container.insert(end(), std::make_pair(key, value));

            auto it = upper_bound_impl(low_it, end(), hash, m_hasher);
            if(it == end())
                return m_container.insert(end(), std::make_pair(key, value));

            if(m_hasher(key) >= m_hasher(it->first))
                ++it;

            return m_container.insert(it, std::make_pair(key, value));
        }

        iterator insert(key_type &&key, value_type &&value)
        {
            size_t hash = m_hasher(key);
            auto p = std::make_pair(std::move(key), std::move(value));
            auto low_it = lower_bound_impl(begin(), end(), hash, m_hasher);
            if(low_it == end())
                return m_container.insert(end(), std::move(p));

            auto it = upper_bound_impl(low_it, end(), hash, m_hasher);
            if(it == end())
                return m_container.insert(end(), std::move(p));

            if(m_hasher(p.first) >= m_hasher(it->first))
                ++it;

            return m_container.insert(it, std::move(p));
        }

        iterator insert(cell_type p)
        {
            size_t hash = m_hasher(p.first);
            auto low_it = lower_bound_impl(begin(), end(), hash, m_hasher);
            if(low_it == end())
                return m_container.insert(end(), std::move(p));

            auto it = upper_bound_impl(low_it, end(), hash, m_hasher);
            if(it == end())
                return m_container.insert(end(), std::move(p));

            if(m_hasher(p.first) >= m_hasher(it->first))
                ++it;

            return m_container.insert(it, std::move(p));
        }

        template<typename... Args>
        iterator emplace(const key_type &key, Args &&... args)
        {
            size_t hash = m_hasher(key);
            auto low_it = lower_bound_impl(begin(), end(), hash, m_hasher);
            if(low_it == end())
                return m_container.insert(end(), std::make_pair(key, value_type { args... }));

            auto it = upper_bound_impl(low_it, end(), hash, m_hasher);
            if(it == end())
                return m_container.insert(end(), std::make_pair(key, value_type { args... }));

            if(m_hasher(key) >= m_hasher(it->first))
                ++it;

            return m_container.insert(it, std::make_pair(key, value_type { args... }));
        }

        iterator erase(const_iterator pos) { return m_container.erase(pos); }

        iterator erase(const_iterator first, const_iterator last)
        {
            return m_container.erase(first, last);
        }

        bool erase(const key_type &key)
        {
            auto it = find(key);
            if(it == end())
                return false;

            m_container.erase(it);
            return true;
        }

        void swap(contiguous_map_type &other) { m_container.swap(other.m_container); }

        value_type_pointer at(const key_type &key)
        {
            auto it = find(key);
            if(it == end())
                return nullptr;

            return &(it->second);
        }

        const_value_type_pointer at(const key_type &key) const
        {
            auto it = find(key);
            if(it == end())
                return nullptr;

            return &(it->second);
        }

        value_type_pointer operator[](const key_type &key) { return at(key); }

        const_value_type_pointer operator[](const key_type &key) const { return at(key); }

        size_t count(const key_type &key) const
        {
            size_t result = 0;
            auto it = find(key);
            while(it != end() && it->first == key)
            {
                ++result;
                ++it;
            }

            return result;
        }

        template<typename Predicate>
        size_t count_if(Predicate pred) const
        {
            size_t result = 0;
            auto it = begin();
            while(it != end())
            {
                if(pred(*it))
                    ++result;

                ++it;
            }

            return result;
        }

        iterator find(const key_type &key) { return find(begin(), end(), key); }

        iterator find(iterator first, iterator last, const key_type &key)
        {
            return find_impl(first, last, key, m_equal, m_hasher);
        }

        const_iterator find(const key_type &key) const { return find(begin(), end(), key); }

        const_iterator find(const_iterator first, const_iterator last, const key_type &key) const
        {
            return find_impl(first, last, key, m_equal, m_hasher);
        }

        template<typename Predicate>
        iterator find_if(Predicate pred)
        {
            return find_if(begin(), end(), pred);
        }

        template<typename Predicate>
        iterator find_if(iterator first, iterator last, Predicate pred)
        {
            return find_if_impl(first, last, pred);
        }

        template<typename Predicate>
        const_iterator find_if(Predicate pred) const
        {
            return find_if(begin(), end(), pred);
        }

        template<typename Predicate>
        const_iterator find_if(const_iterator first, const_iterator last, Predicate pred) const
        {
            return find_if_impl(first, last, pred);
        }

        std::vector<iterator> find_all(const key_type &key)
        {
            return find_all(begin(), end(), key);
        }

        std::vector<iterator> find_all(iterator first, iterator last, const key_type &key)
        {
            return find_all_impl(first, last, key, m_equal, m_hasher);
        }

        std::vector<const_iterator> find_all(const key_type &key) const
        {
            return find_all(begin(), end(), key);
        }

        std::vector<const_iterator> find_all(const_iterator first,
                                             const_iterator last,
                                             const key_type &key) const
        {
            return find_all_impl(first, last, key, m_equal, m_hasher);
        }

        template<typename Predicate>
        iterator find_all_if(Predicate pred)
        {
            return find_all_if(begin(), end(), pred);
        }

        template<typename Predicate>
        iterator find_all_if(iterator first, iterator last, Predicate pred)
        {
            return find_all_if_impl(first, last, pred);
        }

        template<typename Predicate>
        const_iterator find_all_if(Predicate pred) const
        {
            return find_all_if(begin(), end(), pred);
        }

        template<typename Predicate>
        const_iterator find_all_if(const_iterator first, const_iterator last, Predicate pred) const
        {
            return find_all_if_impl(first, last, pred);
        }

        iterator find_last(const key_type &key) { return find_last(begin(), end(), key); }

        iterator find_last(iterator first, iterator last, const key_type &key)
        {
            return find_last_impl(first, last, key, m_equal, m_hasher);
        }

        const_iterator find_last(const key_type &key) const
        {
            return find_last(begin(), end(), key);
        }

        const_iterator find_last(const_iterator first,
                                 const_iterator last,
                                 const key_type &key) const
        {
            return find_last_impl(first, last, key, m_equal, m_hasher);
        }

        template<typename Predicate>
        iterator find_last_if(Predicate pred)
        {
            return find_last_if(begin(), end(), pred);
        }

        template<typename Predicate>
        iterator find_last_if(iterator first, iterator last, Predicate pred)
        {
            return find_last_if_impl(first, last, pred);
        }

        template<typename Predicate>
        const_iterator find_last_if(Predicate pred) const
        {
            return find_last_if(begin(), end(), pred);
        }

        template<typename Predicate>
        const_iterator find_last_if(const_iterator first, const_iterator last, Predicate pred) const
        {
            return find_last_if_impl(first, last, pred);
        }

        bool binary_search(const_iterator first, const_iterator last, const key_type &key) const
        {
            first = lower_bound(first, last, key);
            return (!(first == last) && !(m_hasher(key) < m_hasher(first->first)));
        }

        template<typename Compare>
        bool binary_search(const_iterator first,
                           const_iterator last,
                           const key_type &key,
                           Compare comp) const
        {
            first = lower_bound(first, last, key, comp);
            return (!(first == last) && !(comp(key, first->first)));
        }

        iterator lower_bound(iterator first, iterator last, const key_type &key)
        {
            return lower_bound_impl(first, last, hashKey(key), m_hasher);
        }

        const_iterator lower_bound(const_iterator first,
                                   const_iterator last,
                                   const key_type &key) const
        {
            return lower_bound_impl(first, last, hashKey(key), m_hasher);
        }

        template<typename Compare>
        iterator lower_bound(iterator first, iterator last, const key_type &key, Compare comp)
        {
            return lower_bound_comp_impl(first, last, key, comp);
        }

        template<typename Compare>
        const_iterator lower_bound(const_iterator first,
                                   const_iterator last,
                                   const key_type &key,
                                   Compare comp)
        {
            return lower_bound_comp_impl(first, last, key, comp);
        }

        iterator upper_bound(iterator first, iterator last, const key_type &key)
        {
            return upper_bound_impl(first, last, m_hasher(key), m_hasher);
        }

        const_iterator upper_bound(const_iterator first,
                                   const_iterator last,
                                   const key_type &key) const
        {
            return upper_bound_impl(first, last, m_hasher(key), m_hasher);
        }

        template<typename Compare>
        iterator upper_bound(iterator first, iterator last, const key_type &key, Compare comp)
        {
            return upper_bound_comp_impl(first, last, key, comp);
        }

        template<typename Compare>
        const_iterator upper_bound(const_iterator first,
                                   const_iterator last,
                                   const key_type &key,
                                   Compare comp) const
        {
            return upper_bound_comp_impl(first, last, key, comp);
        }

      protected:
        template<typename IteratorType>
        static IteratorType find_impl(IteratorType first,
                                      IteratorType last,
                                      const key_type &key,
                                      const key_equal_type &equal,
                                      const hasher_type &hasher)
        {
            auto it = lower_bound_impl(first, last, hasher(key), hasher);
            if(it == last)
                return last;

            if(equal(key, it->first))
                return it;

            return last;
        }

        template<typename IteratorType>
        static std::vector<IteratorType> find_all_impl(IteratorType first,
                                                       IteratorType last,
                                                       const key_type &key,
                                                       const key_equal_type &equal,
                                                       const hasher_type &hasher)
        {
            std::vector<IteratorType> result;

            auto it = lower_bound_impl(first, last, hasher(key), hasher);
            if(it == last)
                return result;

            while(equal(key, it->first))
            {
                result.push_back(it);
                ++it;
            }

            return result;
        }

        template<typename IteratorType, typename Predicate>
        static IteratorType find_if_impl(IteratorType first, IteratorType last, Predicate pred)
        {
            while(first != last)
            {
                if(pred(first))
                    break;

                ++first;
            }

            return first;
        }

        template<typename IteratorType, typename Predicate>
        static std::vector<IteratorType> find_all_if_impl(IteratorType first,
                                                          IteratorType last,
                                                          Predicate pred)
        {
            std::vector<IteratorType> result;
            while(first != last)
            {
                if(pred(first))
                    result.push_back(first);

                ++first;
            }

            return result;
        }

        template<typename IteratorType>
        static IteratorType find_last_impl(IteratorType first,
                                           IteratorType last,
                                           const key_type &key,
                                           const key_equal_type &equal,
                                           const hasher_type &hasher)
        {
            auto it = upper_bound_impl(first, last, hasher(key), hasher);
            if(it == first)
                return last;

            --it;
            if(equal(key, it->first))
                return it;

            return last;
        }

        template<typename IteratorType, typename Predicate>
        static IteratorType find_last_if_impl(IteratorType first, IteratorType last, Predicate pred)
        {
            if(first == last)
                return last;

            auto it = last;
            --it;
            while(it > first)
            {
                if(pred(*it))
                    return it;

                --it;
            }

            if(pred(first))
                return first;

            return last;
        }

        template<typename IteratorType>
        static IteratorType lower_bound_impl(IteratorType first,
                                             IteratorType last,
                                             size_t hash,
                                             const hasher_type &hasher)
        {
            IteratorType it;
            difference_type count, step;
            count = std::distance(first, last);

            while(count > 0)
            {
                it = first;
                step = count / 2;
                std::advance(it, step);
                size_t h = hasher(it->first);
                if(h < hash)
                {
                    first = ++it;
                    count -= step + 1;
                }
                else
                    count = step;
            }
            return first;
        }

        template<typename IteratorType, typename Compare>
        static IteratorType lower_bound_comp_impl(IteratorType first,
                                                  IteratorType last,
                                                  const key_type &key,
                                                  Compare comp)
        {
            IteratorType it;
            difference_type count, step;
            count = std::distance(first, last);

            while(count > 0)
            {
                it = first;
                step = count / 2;
                std::advance(it, step);
                if(comp(it->first, key))
                {
                    first = ++it;
                    count -= step + 1;
                }
                else
                    count = step;
            }
            return first;
        }

        template<typename IteratorType>
        static IteratorType upper_bound_impl(IteratorType first,
                                             IteratorType last,
                                             size_t hash,
                                             const hasher_type &hasher)
        {
            IteratorType it;
            typename std::iterator_traits<IteratorType>::difference_type count, step;
            count = std::distance(first, last);

            while(count > 0)
            {
                it = first;
                step = count / 2;
                std::advance(it, step);
                size_t h = hasher(it->first);
                if(hash >= h)
                {
                    first = ++it;
                    count -= step + 1;
                }
                else
                    count = step;
            }
            return first;
        }

        template<typename IteratorType, typename Compare>
        static IteratorType upper_bound_comp_impl(IteratorType first,
                                                  IteratorType last,
                                                  const key_type &key,
                                                  Compare comp)
        {
            IteratorType it;
            typename std::iterator_traits<IteratorType>::difference_type count, step;
            count = std::distance(first, last);

            while(count > 0)
            {
                it = first;
                step = count / 2;
                std::advance(it, step);
                if(!comp(key, it->first))
                {
                    first = ++it;
                    count -= step + 1;
                }
                else
                    count = step;
            }
            return first;
        }
    };

} // namespace FDCore

#endif // FDCORE_CONTIGUOUSMAP_H