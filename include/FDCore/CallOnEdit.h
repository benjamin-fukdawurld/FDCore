#ifndef CALLONEDIT_H
#define CALLONEDIT_H

#include <type_traits>
#include <tuple>

namespace FDCore
{
    namespace internal
    {
        template<bool is_method>
        struct callback_call_helper;

        template<>
        struct callback_call_helper<true>
        {
            template<typename T, typename Callback, typename ...Args>
            static void call(T *caller, Callback cb, Args ...args)
            {
                return caller->*cb(args...);
            }
        };

        template<>
        struct callback_call_helper<false>
        {
            template<typename T, typename Callback, typename ...Args>
            static void call(T*, Callback cb, Args ...args)
            {
                return cb(args...);
            }
        };

    }

    template <typename T, typename Callback, typename ...Args>
    class CallOnEdit
    {
        protected:
            Callback m_cb;
            std::tuple<Args...> m_args;

        public:
            CallOnEdit(Callback cb, Args ...args) :
                m_cb(cb),
                m_args(args...)
            {}

            const T& operator*() const { return *static_cast<T*>(this); }

            T& operator*()
            {
                call();
                return *static_cast<T*>(this);
            }

            const T* operator->() const { return static_cast<T*>(this); }

            T* operator->()
            {
                call();
                return static_cast<T*>(this);
            }

        private:
            void call()
            {
                typedef internal::callback_call_helper<std::is_member_function_pointer_v<Callback>> call_helper;
                std::apply(call_helper::call, std::tuple_cat(static_cast<T*>(this), m_cb, m_args));
            }
    };
}

#endif // CALLONEDIT_H
