#ifndef FUNCTION_ABSTRACT_H
#define FUNCTION_ABSTRACT_H

#include "../../businessLogic.h"
#include "../../Pattern/singleton.h"

#include <memory>
#include <functional>

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(Abstract)

class Product
{
protected:
    Product()
    {
    }
    /* With the virtual destructor, the compiler considers this class to be polymorphic */
    virtual ~Product() = default;
};

END_NAMESPACE // Abstract
END_NAMESPACE // Function
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !FUNCTION_ABSTRACT_H
