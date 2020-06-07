#ifndef SINGLETONTRAIT_H
#define SINGLETONTRAIT_H

#include <memory>
#include <type_traits>

namespace FDCore
{
    template<typename Derived>
    class Singleton
    {
      private:
        static std::unique_ptr<Derived> m_instance;

      protected:
        Singleton() {}

      public:
        template<typename SingletonType = Derived, typename... Args>
        static typename std::enable_if_t<std::is_base_of_v<Derived, SingletonType>, Derived &>
          getInstance(Args... args);

        template<typename SingletonType = Derived, typename... Args>
        static typename std::enable_if_t<std::is_base_of_v<Derived, SingletonType>, const Derived &>
          getInstance(Args... args);
    };

    template<typename Derived>
    template<typename SingletonType, typename... Args>
    std::enable_if_t<std::is_base_of_v<Derived, SingletonType>, Derived &> Singleton<
      Derived>::getInstance(Args... args)
    {
        if(!m_instance)
            m_instance.reset(new SingletonType(args...));

        return *m_instance;
    }

    template<typename Derived>
    template<typename SingletonType, typename... Args>
    std::enable_if_t<std::is_base_of_v<Derived, SingletonType>, const Derived &> Singleton<
      Derived>::getInstance(Args... args)
    {
        if(!m_instance)
            m_instance.reset(new SingletonType(args...));

        return *m_instance;
    }

} // namespace FDCore

#endif // SINGLETONTRAIT_H
