#include <FDCore/ResourceManager.h>

#include <cassert>

FDCore::ResourceManager::ResourceManager(std::initializer_list<AbstractResource *> &&resources)
{
    for(auto r: resources)
        insert(r);
}

FDCore::ResourceManager::~ResourceManager()
{
    clear();
}

const FDCore::ResourceManager::ResourceLoader *FDCore::ResourceManager::getLoader(std::string_view path) const
{
    auto it = std::find_if(m_loaders.begin(),
                           m_loaders.end(),
                           [path](const ResourceLoader &loader)
    { return loader.matches(path); });

    if(it == m_loaders.end())
        return nullptr;

    return &(*it);
}

bool FDCore::ResourceManager::contains(std::string_view name) const
{
    const_iterator first = lower_bound(begin(), end(), name);
    return (first != end() && first->get()->getResourceHash() == std::hash<std::string_view>()(name));
}

FDCore::ResourceManager::raw_pointer FDCore::ResourceManager::operator[](std::string_view name)
{
    iterator first = get(name);
    if(first == end())
        return nullptr;

    return first->get();
}

FDCore::ResourceManager::const_raw_pointer FDCore::ResourceManager::operator[](std::string_view name) const
{
    const_iterator first = get(name);
    if(first == end())
        return nullptr;

    return first->get();
}

FDCore::ResourceManager::raw_pointer FDCore::ResourceManager::at(std::string_view name)
{
    iterator first = get(name);
    if(first == end())
        return nullptr;

    return first->get();
}

FDCore::ResourceManager::const_raw_pointer FDCore::ResourceManager::at(std::string_view name) const
{
    const_iterator first = get(name);
    if(first == end())
        return nullptr;

    return first->get();
}

FDCore::ResourceManager::iterator FDCore::ResourceManager::insert(FDCore::AbstractResource *res)
{
    resource_pointer r(res);
    iterator it = std::lower_bound(begin(), end(), r, [](const resource_pointer &a, const resource_pointer &b) { return *a < *b; });
    assert(it->get()->getResourceHash() != res->getResourceHash() && "resource already registered");
    return m_resources.insert(it, std::move(r));
}

FDCore::ResourceManager::iterator FDCore::ResourceManager::erase(std::string_view name)
{
    iterator it = get(name);
    if(it == end())
        return end();

    (*it)->release();
    return m_resources.erase(it);
}

void FDCore::ResourceManager::clear()
{
    for(resource_pointer &r: m_resources)
        r->release();

    m_resources.clear();
}

FDCore::ResourceManager::const_iterator FDCore::ResourceManager::lower_bound(FDCore::ResourceManager::const_iterator first, FDCore::ResourceManager::const_iterator last, std::string_view k) const
{
    size_t h = std::hash<std::string_view>()(k);
    const_iterator it;
    difference_type count, step;
    count = std::distance(first, last);

    while (count > 0) {
        it = first;
        step = count / 2;
        std::advance(it, step);
        if (it->get()->getResourceHash() < h) {
            first = ++it;
            count -= step + 1;
        }
        else
            count = step;
    }
    return first;
}

FDCore::ResourceManager::iterator FDCore::ResourceManager::lower_bound(FDCore::ResourceManager::const_iterator first, FDCore::ResourceManager::const_iterator last, std::string_view k)
{
    const_iterator it = const_cast<const ResourceManager*>(this)->lower_bound(first, last, k);
    difference_type i = std::distance(cbegin(), it);
    iterator result = begin();
    std::advance(result, i);
    return result;
}

FDCore::ResourceManager::const_iterator FDCore::ResourceManager::upper_bound(FDCore::ResourceManager::const_iterator first, FDCore::ResourceManager::const_iterator last, std::string_view k) const
{
    size_t h = std::hash<std::string_view>()(k);
    const_iterator it;
    difference_type count, step;
    count = std::distance(first, last);

    while (count > 0) {
        it = first;
        step = count / 2;
        std::advance(it, step);
        if (!(h < it->get()->getResourceHash())) {
            first = ++it;
            count -= step + 1;
        }
        else
            count = step;
    }
    return first;
}

FDCore::ResourceManager::iterator FDCore::ResourceManager::upper_bound(FDCore::ResourceManager::const_iterator first, FDCore::ResourceManager::const_iterator last, std::string_view k)
{
    const_iterator it = const_cast<const ResourceManager*>(this)->upper_bound(first, last, k);
    difference_type i = std::distance(cbegin(), it);
    iterator result = begin();
    std::advance(result, i);
    return result;
}

FDCore::ResourceManager::iterator FDCore::ResourceManager::get(std::string_view name)
{
    size_t h = std::hash<std::string_view>()(name);
    iterator first = lower_bound(begin(), end(), name);
    if(first == end() || first->get()->getResourceHash() != h)
        return end();

    return first;
}

FDCore::ResourceManager::const_iterator FDCore::ResourceManager::get(std::string_view name) const
{
    size_t h = std::hash<std::string_view>()(name);
    const_iterator first = lower_bound(begin(), end(), name);
    if(first == end() || first->get()->getResourceHash() != h)
        return end();

    return first;
}

FDCore::ResourceManager::iterator FDCore::ResourceManager::getFromPath(std::string_view path)
{
    return std::find_if(m_resources.begin(), m_resources.end(), [path](const resource_pointer &ptr)
    {
        return ptr->getResourcePath() == path;
    });
}

FDCore::ResourceManager::const_iterator FDCore::ResourceManager::getFromPath(std::string_view path) const
{
    return std::find_if(m_resources.begin(), m_resources.end(), [path](const resource_pointer &ptr)
    {
        return ptr->getResourcePath() == path;
    });
}
