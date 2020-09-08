#ifndef FDCORE_DYNAMICVARIABLE_H
#define FDCORE_DYNAMICVARIABLE_H

#include <FDCore/DynamicVariable/AbstractValue.h>
#include <memory>

namespace FDCore
{
    class DynamicVariable
    {
      private:
        std::shared_ptr<AbstractValue> m_value;

        DynamicVariable();
    };

} // namespace FDCore

#endif // FDCORE_DYNAMICVARIABLE_H