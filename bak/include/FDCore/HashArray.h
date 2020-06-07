#ifndef FDCORE_HASHARRAY_H
#define FDCORE_HASHARRAY_H

#include <algorithm>
#include <vector>


template<typename Key, typename T, typename Hash = std::hash<T>>
class HashArray
{
  public:
    typedef Key key_type;
    typedef Hash hash_type;
    typedef T value_type;
    typedef typename std::vector<std::pair<size_t, T>>::allocator_type allocator_type;
    typedef typename std::vector<std::pair<size_t, T>>::size_type size_type;
    typedef typename std::vector<std::pair<size_t, T>>::difference_type difference_type;
    typedef value_type &reference;
    typedef const reference const_reference;
    typedef value_type *pointer;
    typedef const pointer const_pointer;
    typedef typename std::vector<std::pair<size_t, T>>::iterator iterator;
    typedef typename std::vector<std::pair<size_t, T>>::const_iterator const_iterator;
    typedef typename std::vector<std::pair<size_t, T>>::reverse_iterator reverse_iterator;
    typedef
      typename std::vector<std::pair<size_t, T>>::const_reverse_iterator const_reverse_iterator;


  protected:
    std::vector<std::pair<size_t, T>> m_data;

  public:
    HashArray(size_t size) { m_data.reserve(size); }

    void insert(const key_type &key, const reference value)
    {
        auto p = std::make_pair<size_t, value_type>(hash_type()(key), value);
        m_data.insert(std::lower_bound(
                        m_data.begin(), m_data.end(), p,
                        [](const std::pair<size_t, value_type> &a,
                           const std::pair<size_t, value_type> &b) { return a.first < b.first; }) -
                        1,
                      p);
    }

    void push(const key_type &key, const reference value)
    {
        m_data.push_back(std::make_pair<size_t, value_type>(hash_type()(key), value));
    }

    void emplace(const key_type &key, const reference value)
    {
        m_data.emplace_back(std::make_pair<size_t, value_type>(hash_type()(key), value));
    }


    reference &operator[](const key_type &key) { return m_data[find()->second]; }


    const reference &operator[](const key_type &key) const { return m_data[find()->second]; }


    bool contains(const key_type &key) const { return find() != m_data.end(); }


    const_iterator find(const key_type &key) const
    {
        const_iterator it = std::lower_bound(
          m_data.begin(), m_data.end(), p,
          [](const std::pair<size_t, value_type> &a, const std::pair<size_t, value_type> &b) {
              return a.first < b.first;
          });

        if(it->first != key)
            return m_data.end();

        return it;
    }


    iterator find(const key_type &key)
    {
        iterator it = std::lower_bound(
          m_data.begin(), m_data.end(), p,
          [](const std::pair<size_t, value_type> &a, const std::pair<size_t, value_type> &b) {
              return a.first < b.first;
          });

        if(it->first != key)
            return m_data.end();

        return it;
    }
};

#endif // FDCORE_HASHARRAY_H