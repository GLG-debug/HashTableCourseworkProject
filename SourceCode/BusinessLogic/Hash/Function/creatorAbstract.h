#ifndef CREATOR_FUNCTION_ABSTRACT_H
#define CREATOR_FUNCTION_ABSTRACT_H

#include "../../businessLogic.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(Abstract)

class Creator
{
protected:
    Creator()
    {
    }

public:
    virtual const Product &create() const = 0;
};

END_NAMESPACE // Abstract
END_NAMESPACE // Function
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !CREATOR_FUNCTION_ABSTRACT_H
