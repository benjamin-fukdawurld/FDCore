#ifndef FDCORE_RESOURCEMANAGER_H
#define FDCORE_RESOURCEMANAGER_H

#include <FDCore/AbstractResource.h>
#include <vector>
#include <memory>

namespace FDCore
{
    class ResourceManager
    {
        public:
            typedef std::unique_ptr<FDCore::AbstractResource> resource_pointer;
            typedef std::vector<resource_pointer> container_type;
            typedef FDCore::AbstractResource* raw_pointer;
            typedef const FDCore::AbstractResource* const_raw_pointer;
            typedef container_type::pointer pointer;
            typedef container_type::const_pointer const_pointer;
            typedef container_type::reference reference;
            typedef container_type::const_reference	const_reference;
            typedef container_type::iterator iterator;
            typedef container_type::const_iterator const_iterator;
            typedef container_type::const_reverse_iterator const_reverse_iterator;
            typedef container_type::reverse_iterator reverse_iterator;
            typedef container_type::size_type size_type;
            typedef container_type::difference_type difference_type;
            typedef container_type::allocator_type allocator_type;
            typedef std::function<bool(std::string_view)> resource_loader_matcher;
            typedef std::function<resource_pointer(std::string_view)> resource_loader_function;

            struct ResourceLoader
            {
                resource_loader_matcher matcher;
                resource_loader_function loader;

                explicit ResourceLoader() = default;
                ResourceLoader(resource_loader_matcher matcher, resource_loader_function loader):
                    matcher(matcher),
                    loader(loader)
                {}

                operator bool() const { return matcher && loader; }

                bool matches(std::string_view path) const
                {
                    return matcher(path);
                }

                resource_pointer load(std::string_view path) const
                {
                    return loader(path);
                }
            };

        protected:
            std::vector<std::unique_ptr<FDCore::AbstractResource>> m_resources;
            std::vector<ResourceLoader> m_loaders;

        public:
            ResourceManager() = default;
            ResourceManager(std::initializer_list<FDCore::AbstractResource*> &&m_resources);

            virtual ~ResourceManager();

            const ResourceLoader *getLoader(std::string_view path) const;

            iterator begin() { return m_resources.begin(); }

            const_iterator begin() const { return m_resources.begin(); }

            iterator end() { return m_resources.end(); }

            const_iterator end() const { return m_resources.end(); }

            reverse_iterator rbegin() { return m_resources.rbegin(); }

            const_reverse_iterator rbegin() const { return m_resources.rbegin(); }

            reverse_iterator rend() { return m_resources.rend(); }

            const_reverse_iterator rend() const { return m_resources.rend(); }

            const_iterator cbegin() const { return m_resources.cbegin(); }

            const_iterator cend() const { return m_resources.cend(); }

            const_reverse_iterator crbegin() const { return m_resources.crbegin(); }

            const_reverse_iterator crend() const { return m_resources.crend(); }

            size_type size() const { return m_resources.size(); }

            size_type max_size() const { return m_resources.max_size(); }

            bool empty() const { return m_resources.empty(); }

            bool isEmpty() const { return m_resources.empty(); }

            void reserve(size_type s) { return m_resources.reserve(s); }

            bool contains(std::string_view name) const;

            raw_pointer operator[](std::string_view name);

            const_raw_pointer operator[](std::string_view name) const;

            raw_pointer at(std::string_view name);

            const_raw_pointer at(std::string_view name) const;

            bool containsPath(std::string_view path) const;
            raw_pointer searchPath(std::string_view path);
            const_raw_pointer searchPath(std::string_view path) const;

            iterator insert(AbstractResource *res);

            template<typename T, typename ...Args>
            iterator emplace(Args ...args)
            {
                return insert(std::make_unique<T>(args...));
            }

            iterator erase(std::string_view name);

            void clear();

            const_iterator lower_bound(const_iterator first, const_iterator last, std::string_view k) const;

            iterator lower_bound(const_iterator first, const_iterator last, std::string_view k);

            template<typename Predicate>
            const_iterator lower_bound(const_iterator first, const_iterator last, Predicate pred) const;

            template<typename Predicate>
            const_iterator lower_bound(const_iterator first, const_iterator last, Predicate pred);

            const_iterator upper_bound(const_iterator first, const_iterator last, std::string_view k) const;

            iterator upper_bound(const_iterator first, const_iterator last, std::string_view k);

            template<class Predicate>
            const_iterator upper_bound(const_iterator first, const_iterator last, Predicate pred) const;

            template<typename Predicate>
            const_iterator upper_bound(const_iterator first, const_iterator last, Predicate pred);

        private:
            iterator get(std::string_view name);
            const_iterator get(std::string_view name) const;

            iterator getFromPath(std::string_view path);
            const_iterator getFromPath(std::string_view path) const;
    };

    template<typename Predicate>
    ResourceManager::const_iterator ResourceManager::lower_bound(const_iterator first, const_iterator last, Predicate pred) const
    {
        const_iterator it;
        difference_type count, step;
        count = std::distance(first, last);

        while (count > 0) {
            it = first;
            step = count / 2;
            std::advance(it, step);
            if(pred(*it))
            {
                first = ++it;
                count -= step + 1;
            }
            else
                count = step;
        }
        return first;
    }

    template<typename Predicate>
    ResourceManager::const_iterator ResourceManager::lower_bound(const_iterator first, const_iterator last, Predicate pred)
    {
        const_iterator it = const_cast<const ResourceManager*>(this)->lower_bound(first, last, pred);
        difference_type i = std::distance(cbegin(), it);
        iterator result = begin();
        std::advance(result, i);
        return result;
    }

    template<class Predicate>
    ResourceManager::const_iterator ResourceManager::upper_bound(const_iterator first, const_iterator last, Predicate pred) const
    {
        const_iterator it;
        difference_type count, step;
        count = std::distance(first, last);

        while (count > 0) {
            it = first;
            step = count / 2;
            std::advance(it, step);
            if (!pred(*it)) {
                first = ++it;
                count -= step + 1;
            }
            else
                count = step;
        }
        return first;
    }

    template<typename Predicate>
    ResourceManager::const_iterator ResourceManager::upper_bound(const_iterator first, const_iterator last, Predicate pred)
    {
        const_iterator it = const_cast<const ResourceManager*>(this)->lower_bound(first, last, pred);
        difference_type i = std::distance(cbegin(), it);
        iterator result = begin();
        std::advance(result, i);
        return result;
    }
}

#endif // FDCORE_RESOURCEMANAGER_H
