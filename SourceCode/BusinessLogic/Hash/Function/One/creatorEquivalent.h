#ifndef CREATOR_FUNCTION_EQUIVALENT_H
#define CREATOR_FUNCTION_EQUIVALENT_H


#include "creatorOne.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(Equivalent)

class Creator : public One::Creator
{
public:
    virtual const Product &create() const override {
        return Product::getInstance();
    }
};

END_NAMESPACE //  Equivalent
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // !CREATOR_FUNCTION_EQUIVALENT_H
