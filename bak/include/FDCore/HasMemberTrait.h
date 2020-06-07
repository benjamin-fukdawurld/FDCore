#ifndef FDCORE_HASMEMBERTRAIT_H
#define FDCORE_HASMEMBERTRAIT_H


#include <type_traits>

#define createMemberChecker(memberName)                                                     \
    namespace FDCore                                                                        \
    {                                                                                       \
        namespace internal                                                                  \
        {                                                                                   \
            template<typename T, typename A0>                                               \
            static auto test_##memberName(int)                                              \
              -> sfinae_true<decltype(std::declval<T>().##memberName(std::declval<A0>()))>; \
            template<typename, typename A0>                                                 \
            static auto test_##memberName(long) -> std::false_type;                         \
        }                                                                                   \
                                                                                            \
        template<class T, class Arg>                                                        \
        struct has_##memberName : decltype(internal::test_##memberName<T, Arg>(0))          \
        {                                                                                   \
        };                                                                                  \
    }

namespace FDCore
{
    namespace internal
    {
        template<typename>
        struct sfinae_true : std::true_type
        {
        };

        template<typename>
        struct sfinae_false : std::false_type
        {
        };
    } // namespace internal
} // namespace FDCore

#endif // !FDCORE_HASMEMBERTRAIT_H
