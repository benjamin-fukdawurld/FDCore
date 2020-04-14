#ifndef CALLONEDIT_H
#define CALLONEDIT_H

#include <functional>

namespace FDCore
{
    template <typename T>
    class CallOnEdit
    {
        protected:
            T *m_managed;
            std::function<void(T&)> m_callback;

        public:
            CallOnEdit():
                CallOnEdit(nullptr)
            {}

            CallOnEdit(T *managed):
                m_managed(managed)
            {}

            template<typename CallbackType>
            CallOnEdit(T *managed, CallbackType cb):
                m_managed(managed),
                m_callback(cb)
            {}

            template<typename CallbackType, typename ...Args>
            CallOnEdit(T *managed, CallbackType cb, Args... args):
                m_managed(managed),
                m_callback(std::bind(cb, args..., std::placeholders::_1))
            {}

            std::function<void(T&)> getCallback() const
            {
                return m_callback;
            }

            template<typename CallbackType>
            void setCallback(CallbackType cb)
            {
                m_callback = cb;
            }

            template<typename CallbackType, typename ...Args>
            void setCallback(CallbackType cb, Args... args)
            {
                m_callback = std::bind(cb, args..., std::placeholders::_1);
            }

            const T *getManagedObject() const { return m_managed; }

            T *getManagedObject()
            {
                if(m_callback)
                    m_callback(*m_managed);

                return m_managed;
            }

            void setManagedObject(T *managed)
            {
                m_managed = managed;
            }

            const T& operator*() const { return *getManagedObject(); }

            T& operator*() { return *getManagedObject(); }

            const T* operator->() const { return getManagedObject(); }

            T* operator->() { return getManagedObject(); }
    };
}

#endif // CALLONEDIT_H
