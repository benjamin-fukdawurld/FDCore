#ifndef FDCORE_DYNAMICVARIABLE_CONVERSION_H
#define FDCORE_DYNAMICVARIABLE_CONVERSION_H

#include <FDCore/DynamicVariable/DynamicVariable_fwd.h>

namespace FDCore
{
    template<class T>
    inline constexpr bool isDynamicVariableConvertible = DynamicVariableConverter<T>::isConvertible;

    template<>
    struct DynamicVariableConverter<bool>
    {
        constexpr static bool isConvertibe = true;

        static DynamicVariable toDynamicVariable(bool value) { return DynamicVariable(value); }

        static bool fromDynamicVariable(const DynamicVariable &value)
        {
            return static_cast<bool>(value);
        }
    };

    template<>
    struct DynamicVariableConverter<DynamicVariable::StringType>
    {
        constexpr static bool isConvertibe = true;

        static DynamicVariable toDynamicVariable(const DynamicVariable::StringType &value)
        {
            return DynamicVariable(value);
        }

        static DynamicVariable::StringType fromDynamicVariable(const DynamicVariable &value)
        {
            return static_cast<DynamicVariable::StringType>(value);
        }
    };



    template<typename T>
    struct DynamicVariableConverter<
      T,
      std::enable_if_t<!std::is_same_v<bool, T> && std::is_integral_v<T>>>
    {
        DynamicVariable toDynamicVariable(const T &value) { return DynamicVariable(value); }

        T fromDynamicVariable(const DynamicVariable &value) { return static_cast<T>(value); }
    };

    template<typename T>
    struct DynamicVariableConverter<T, std::enable_if_t<!std::is_floating_point_v<T>>>
    {
        DynamicVariable toDynamicVariable(const T &value) { return DynamicVariable(value); }

        T fromDynamicVariable(const DynamicVariable &value) { return static_cast<T>(value); }
    };

    /*template<typename T>
    struct DynamicVariableConverter<std::vector<T>,
                                    std::enable_if_t<std::is_base_of_v<AbstractValue, T>>>
    {
        DynamicVariable toDynamicVariable(const std::vector<T> &value){ return
    DynamicVariable(value); }

        T fromDynamicVariable(const DynamicVariable &value) { return static_cast<T>(value); }
    };*/

} // namespace FDCore

#endif // FDCORE_DYNAMICVARIABLE_CONVERSION_H
