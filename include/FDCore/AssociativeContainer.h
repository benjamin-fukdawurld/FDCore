#ifndef ASSOCIATIVECONTAINER_H
#define ASSOCIATIVECONTAINER_H

#include <functional>
#include <optional>
#include <vector>

#include <FDCore/ComparableTrait.h>

namespace FDCore
{
    /**
     * @brief KeyType struct represents the kay type of an associative contiguous container
     *
     * @tparam Key the type to hash as key
     * @tparam Hash the hashing strategy to use. The expected type is similar to std::unordered_map hash, default value: std::hash<Key>
     */
    template<typename Key, typename Hash = std::hash<Key>>
    struct KeyType : public ComparableTrait<KeyType<Key, Hash>>
    {
        size_t hash; ///< the hash value of the key
        #ifdef DEBUG
        Key key ///< the key itself. This value is used only for debug purpose and is not present in release mode
        #endif

        /**
         * @brief Constructs a new KeyType object with the key and a hasher
         *
         * @param k the key value
         * @param h the hasher to use to hash the key
         */
        KeyType(const Key &k, const Hash &h) :
            hash(h(k))
            #ifdef DEBUG
            , key(k)
            #endif
        {}

        /**
         * @brief Compares 2 KeyType according to their hashed value.
         *        The returned value is the result of this->hash - other.hash
         *
         * @param other the KeyType to compare with the current one
         * @return the result of this->hash - other.hash as int64_t
         */
        int64_t compare(const KeyType &other) const { return hash - other.hash; }
    };

    /**
     * @brief KeyValueType is the cell type of an associative contiguous container
     *
     * @tparam Key the type to use as key
     * @tparam T the value contained in the cell
     * @tparam Hash the hashing strategy to use. The expected type is similar to std::unordered_map hash, default value: std::hash<Key>
     */
    template<typename Key, typename T, class Hash = std::hash<Key>>
    struct KeyValueType : public ComparableTrait<KeyValueType<Key, T, Hash>>,
                          public ComparableTrait<KeyType<Key, Hash>>
    {
        KeyType<Key, Hash> key; ///< the key of the cell
        T value; ///< the value of the cell

        /**
         * @brief Constructs a new Key Value Type object
         *
         * @param k the key of the cell
         * @param value the value of the cell
         * @param h the hasher to use to hash the key
         */
        KeyValueType(Key &&k, T &&value, const Hash &h):
            key(std::move(k), h),
            value(std::move(value))
        {}

        /**
         * @brief Constructs a new Key Value Type object
         *
         * @param k the key of the cell
         * @param value the value of the cell
         * @param h the hasher to use to hash the key
         */
        KeyValueType(const Key &k, const T &value, const Hash &h):
            key(k, h),
            value(value)
        {}

        /**
         * @brief Compares a cell with a key
         *
         * @param key the key to compare with the current cell
         * @return the result of this->key.compare(key) int64_t
         */
        int64_t compare(const KeyType<Key, Hash> &key) const { return key.compare(key); }

        /**
         * @brief Compares a cell with a key
         *
         * @param key the key to compare with the current cell
         * @return the result of this->key.compare(key) int64_t
         */
        int64_t compare(const KeyValueType &other) const { return compare(other.key); }
    };

    /**
     * @brief AssociativeContainer is an associative container with contiguous storage.
     *        It behaves like a std::unordered_map but each element is stored next to each other
     *
     * @tparam Key the key type use to access the elements
     * @tparam T the value type of the elements
     * @tparam Hash the hashing strategy to use. The expected type is similar to std::unordered_map hash, default value: std::hash<Key>
     * @tparam Allocator the allocation strategy to use. The expected type is similar to stl containers' allocator default, value: std::allocator<KeyValueType<Key, T, Hash>>
     */
    template<typename Key, typename T, typename Hash = std::hash<Key>,
             typename Allocator = std::allocator<KeyValueType<Key, T, Hash>>>
    class AssociativeContainer
    {
        public:
            typedef Key key_type; ///< the container key type
            typedef T value_type; ///< the container value type
            typedef KeyType<Key, Hash> cell_key_type; ///< the container cell key type. This is the type used to compare two elements
            typedef KeyValueType<Key, T, Hash> cell_type; ///< the container cell type
            typedef size_t size_type; ///< the container size type
            typedef ptrdiff_t difference_type; ///< signed integer used to check distance between two cells
            typedef Hash hasher; ///< the container hasher type
            typedef Allocator allocator_type; ///< the container allocator type
            typedef cell_type& reference; ///< the container cell reference type
            typedef const cell_type& const_reference; ///< the container cell const reference type
            typedef cell_type* pointer; ///< the container cell pointer type
            typedef const cell_type* const_pointer; ///< the container cell const pointer type
            typedef std::vector<cell_type, allocator_type> container_type; ///< the container underlying containing structure reference type
            typedef typename container_type::iterator iterator; ///< the container iterator type
            typedef typename container_type::const_iterator const_iterator; ///< the container const iterator type
            typedef typename container_type::reverse_iterator reverse_iterator; ///< the container reverse iterator type
            typedef typename container_type::const_reverse_iterator const_reverse_iterator;  ///< the container const reverse iterator type

        protected:
            container_type m_container; ///< the underlying containing struture of the associative container
            hasher m_hash; ///< the hasher of the container

        public:
            /**
             * @brief Returns an hash value for a given key
             * @param key the key to hash
             * @return an hash value for a given key
             */
            size_t hashKey(key_type key) { return m_hash(key); }
            
            /**
             * @brief Finds a cell in the container given its key
             *
             * @param k the key to search for
             * @return an iterator on the found result or an iterator on the end of the container
             */
            iterator find(const key_type &k)
            {
                return std::lower_bound(begin(), end(), KeyType{ k, m_hash });
            }

            /**
             * @brief Finds a cell in the container given its key
             *
             * @param k the key to search for
             * @return an iterator on the found result if any or an iterator on the end of the container
             */
            const_iterator find(const key_type &k) const
            {
                return std::lower_bound(begin(), end(), KeyType{ k, m_hash });
            }

            /**
             * @brief Finds the first cell in the container that matches a predicate
             *
             * @tparam Predicate the predicate type. This type must match the same requirements as std::find
             * @param pred the predicate to check the cells
             * @return an iterator on the first cell that matches the predicate if any or the end of the container
             */
            template<typename Predicate>
            iterator find_if(Predicate pred)
            {
                return std::find_if(begin(), end(), pred);
            }

            /**
             * @brief Finds the first cell in the container that matches a predicate
             *
             * @tparam Predicate the predicate type. This type must match the same requirements as std::find
             * @param pred the predicate to check the cells
             * @return an iterator on the first cell that matches the predicate if any or the end of the container
             */
            template<typename Predicate>
            const_iterator find_if(Predicate pred) const
            {
                return std::find_if(begin(), end(), pred);
            }

            /**
             * @brief Finds all cells in the container that matches a predicate
             *
             * @tparam Predicate the predicate type. This type must match the same requirements as std::find
             * @param pred the predicate to check the cells
             * @return an array of iterators to the matched cells as std::vector<iterator>
             */
            template<typename Predicate>
            std::vector<iterator> find_all_if(Predicate pred)
            {
                std::vector<iterator> result;
                auto it = begin();
                auto last = end();
                while((it = std::find_if(it, last, pred)) != last) {
                    result.push_back(it);
                    ++it;
                }

                return result;
            }

            /**
             * @brief Finds all cells in the container that matches a predicate
             *
             * @tparam Predicate the predicate type. This type must match the same requirements as std::find
             * @param pred the predicate to check the cells
             * @return an array of iterators to the matched cells as std::vector<iterator>
             */
            template<typename Predicate>
            std::vector<const_iterator> find_all_if(Predicate pred) const
            {
                std::vector<const_iterator> result;
                auto it = begin();
                auto last = end();
                while((it = std::find_if(it, last, pred)) != last) {
                    result.push_back(it);
                    ++it;
                }

                return result;
            }

            /**
             * @brief Checks if the container as a cell with the given key
             *
             * @param k the key value to check
             * @return true if there is a cell with this key false otherwise
             */
            bool contains(const key_type &k) const
            {
                return find(k) != end();
            }


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
            hasher hash_function() const { return m_hash; }

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
             * @brief Reserves storage, if size is less than or equal to the current size of the container it does nothing
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

            /**
             * @brief Inserts a value within a given key
             *
             * @param k the key of the new cell
             * @param value the value of the new cell
             * @return an iterator pointing to the inserted value
             */
            iterator insert(const key_type &k, const value_type &value)
            {
                cell_type cell(k, value, m_hash);
                iterator it = std::lower_bound(m_container.begin(), m_container.end(), cell);
                return m_container.insert(it, std::move(cell));
            }

            /**
             * @brief Inserts a value within a given key
             *
             * @param k the key of the new cell
             * @param value the value of the new cell
             * @return an iterator pointing to the inserted value
             */
            iterator insert(key_type &&k, value_type &&value)
            {
                cell_type cell(std::move(k), std::move(value), m_hash);
                iterator it = std::lower_bound(m_container.begin(), m_container.end(), cell);
                return m_container.insert(it, std::move(cell));
            }

            /**
             * @brief Erases a cell from the container
             * @param it an iterator on the cell to erase
             * @return An iterator pointing to the new location
             * of the element that followed the last element erased by the function call.
             * This is the container end if the operation erased the last element in the sequence.
             */
            iterator erase(const_iterator it)
            {
                return m_container.erase(it);
            }

            /**
             * @brief Erases cells from the container
             * @param first the begining of the sequence to erase
             * @param last the end of the sequence to erase
             * @return An iterator pointing to the new location
             * of the element that followed the last element erased by the function call.
             * This is the container end if the operation erased the last element in the sequence.
             */
            iterator erase(const_iterator first, const_iterator last)
            {
                return m_container.erase(first, last);
            }

            /**
             * @brief Erase an element from the container given its key
             *
             * @param k the key of the element to erase
             * @return an iterator following the removed element
             */
            iterator erase(const key_type &k)
            {
                return m_container.erase(find(k));
            }

            /**
             * @brief Erase an element from the container if it matches a predicate
             *
             * @tparam
             * @tparam Predicate the predicate type. This type must match the same requirements as std::find
             * @param pred the predicate to check the cells
             * @return an iterator following the removed element
             */
            template<typename Predicate>
            iterator erase_if(Predicate pred)
            {
                return m_container.erase(find_if(pred));
            }

            /**
             * @brief Counts the number of elements with the key @p key
             *
             * @param k the key to search
             * @return the number of element with the key @p key
             */
            size_type count(const key_type &k) const
            {
                return std::count(begin(), end(), KeyType{ k, m_hash });
            }

            /**
             * @brief Counts the number of elements that match a predicate
             *
             * @tparam Predicate the predicate type. This type must match the same requirements as std::count_if
             * @param pred the predicate to check the cells
             * @return the number of element with the key @p key
             */
            template<typename Predicate>
            size_type count_if(Predicate pred) const
            {
                return std::count_if(begin(), end(), pred);
            }

            /**
             * @brief Swaps the container's content with another container
             *
             * @param other the container to swap
             */
            void swap(AssociativeContainer &other) { m_container.swap(other); }

            /**
             * @brief Returns a pointer to the cell that has a given key
             * @param k the key to search
             * @return a pointer to the cell that has a given key if there is no such key in the
             * container a null pointer is returned
             */
            pointer at(const key_type &k)
            {
                iterator it = find(k);
                if(it == end())
                    return nullptr;

                return &(*it);
            }

            /**
             * @brief Returns a const pointer to the cell that has a given key
             * @param k the key to search
             * @return a const pointer to the cell that has a given key if there is no such key in the
             * container a null pointer is returned
             */
            const_pointer at(const key_type &k) const
            {
                const_iterator it = find(k);
                if(it == end())
                    return nullptr;

                return &(*it);
            }

            /**
             * @brief Returns a pointer to the cell that has a given key
             * @param k the key to search
             * @return a pointer to the cell that has a given key if there is no such key in the
             * container a null pointer is returned
             */
            pointer operator[](const key_type &k)
            {
                return at(k);
            }

            /**
             * @brief Returns a const pointer to the cell that has a given key
             * @param k the key to search
             * @return a const pointer to the cell that has a given key if there is no such key in the
             * container a null pointer is returned
             */
            const_pointer operator[](const key_type &k) const
            {
                return at(k);
            }
    };
}

#endif // ASSOCIATIVECONTAINER_H
