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
        const size_t hash; ///< the hash value of the key
        #ifdef DEBUG
        const Key key ///< the key itself. This value is used only for debug purpose and is not present in release mode
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
        int64_t compare(const KeyType &other) { return hash - other.hash; }
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
        int64_t compare(const KeyType<Key, Hash> &key) { return key.compare(key); }

        /**
         * @brief Compares a cell with a key
         *
         * @param key the key to compare with the current cell
         * @return the result of this->key.compare(key) int64_t
         */
        int64_t compare(const KeyValueType &other) { return compare(other.key); }
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
                while((it = std::find_if(it, last, pred)) != last)
                    result.push_back(it);

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
