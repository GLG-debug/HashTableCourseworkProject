#ifndef CREATOR_FUNCTION_STANDART_H
#define CREATOR_FUNCTION_STANDART_H

#include "creatorOne.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(Standart)

class Creator : public One::Creator
{
public:
    virtual const Product &create() const override {
        return Product::getInstance();
    }
};

END_NAMESPACE //  Standart
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // !CREATOR_FUNCTION_FNV1a_H
