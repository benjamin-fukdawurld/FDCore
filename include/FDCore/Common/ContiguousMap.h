#ifndef FDCORE_CONTIGUOUSMAP_H
#define FDCORE_CONTIGUOUSMAP_H

#include <functional>
#include <vector>


namespace FDCore
{
    template<typename Key, typename T, typename Hash = std::hash<Key>,
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


      protected:
        container_type m_container;
        hasher_type m_hasher;
        key_equal_type m_equal;

      public:
        explicit ContiguousMap(const Hash &hash = Hash(),
                               const key_equal_type &equal = key_equal_type(),
                               const Allocator &alloc = Allocator());

        /**
         * @brief Returns an hash value for a given key
         * @param key the key to hash
         * @return an hash value for a given key
         */
        size_t hashKey(key_type key) const { return m_hash(key); }

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

        std::pair<iterator, bool> insert(const value_type &value) {}

        std::pair<iterator, bool> insert(value_type &&value);
        template<class P>
        std::pair<iterator, bool> insert(P &&value);

        iterator lower_bound(iterator first, iterator last, consy key_type &key)
        {
            return lower_bound_impl(first, last, hashKey(key));
        }

        const_iterator lower_bound(const_iterator first, const_iterator last,
                                   consy key_type &key) const
        {
            return lower_bound_impl(first, last, hashKey(key));
        }

      protected:
        template<typename ForwardIt>
        static ForwardIt lower_bound_impl(ForwardIt first, ForwardIt last, size_t hash)
        {
            ForwardIt it;
            difference_type count, step;
            count = std::distance(first, last);

            while(count > 0)
            {
                it = first;
                step = count / 2;
                std::advance(it, step);
                if(hashKey(it->first) < hash)
                {
                    first = ++it;
                    count -= step + 1;
                }
                else
                    count = step;
            }
            return first;
        }

        template<typename ForwardIt, typename Compare>
        static ForwardIt lower_bound_impl(ForwardIt first, ForwardIt last, const key_type &key,
                                          Compare comp)
        {
            ForwardIt it;
            difference_type count, step;
            count = std::distance(first, last);

            while(count > 0)
            {
                it = first;
                step = count / 2;
                std::advance(it, step);
                if(Compare(it->first, key))
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

    template<typename T, typename Hash = std::hash<T>, typename Equal = std::equal_to<T>,
             typename Allocator = std::allocator<T>>
    class ContiguousSet
    {
      public:
        typedef T value_type;                   ///< the container value type
        typedef value_type *value_type_pointer; ///< a pointer to the container value type
        typedef const value_type
          *const_value_type_pointer; ///< a constant pointer to the container value type
        typedef value_type &value_type_reference; ///< a reference to the container value type
        typedef const value_type
          &const_value_type_reference; ///< a constant reference to the container value type
        typedef size_t size_type;      ///< the container size type
        typedef ptrdiff_t
          difference_type;        ///< signed integer used to check distance between two cells
        typedef Hash hasher_type; ///< the container hasher type
        typedef Equal key_equal_type;
        typedef Allocator allocator_type;          ///< the container allocator type
        typedef value_type &reference;             ///< the container cell reference type
        typedef const value_type &const_reference; ///< the container cell const reference type
        typedef value_type *pointer;               ///< the container cell pointer type
        typedef const value_type *const_pointer;   ///< the container cell const pointer type
        typedef std::vector<value_type, allocator_type>
          container_type; ///< the container underlying containing structure reference type
        typedef typename container_type::iterator iterator; ///< the container iterator type
        typedef typename container_type::const_iterator
          const_iterator; ///< the container const iterator type
        typedef typename container_type::reverse_iterator
          reverse_iterator; ///< the container reverse iterator type
        typedef typename container_type::const_reverse_iterator
          const_reverse_iterator; ///< the container const reverse iterator type


      protected:
        container_type m_container;
        hasher_type m_hasher;
        key_equal_type m_equal;

      public:
        explicit ContiguousSet(const Hash &hash = Hash(),
                               const key_equal_type &equal = key_equal_type(),
                               const Allocator &alloc = Allocator());

        size_t hashValue(value_type value) const { return m_hash(value); }
    };
} // namespace FDCore

#endif // FDCORE_CONTIGUOUSMAP_H