#ifndef FDCORE_OBJECTGUARD_H
#define FDCORE_OBJECTGUARD_H

namespace FDCore
{
    template<typename T,
             typename InitFunction = std::function<bool(T &)>,
             typename QuitFunction = std::function<void(T &)>>
    class ObjectGuard
    {
      private:
        T &m_object;
        InitFunction m_init;
        QuitFunction m_quit;
        bool m_isInitialized;

      public:
        ObjectGuard(T &object) :
            ObjectGuard(
              object, [](T &obj) { return obj.init(); }, [](T &obj) { obj.quit(); })
        {
        }

        ObjectGuard(T &object, InitFunction init, QuitFunction quit) :
            m_object(object),
            m_init(init),
            m_quit(quit),
            m_isInitialized(false)
        {
            m_isInitialized = m_init(m_object);
        }

        ~ObjectGuard()
        {
            if(m_isInitialized)
                m_quit(m_object);
        }

        T &operator*() { return m_object; }
        const T &operator*() const { return m_object; }

        T *operator->() { return &m_object; }
        const T *operator->() const { return &m_object; }

        operator bool() const { return m_isInitialized; }
    };
} // namespace FDCore

#endif // FDCORE_OBJECTGUARD_H