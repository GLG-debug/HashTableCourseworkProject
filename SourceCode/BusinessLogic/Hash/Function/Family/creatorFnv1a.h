#ifndef CREATOR_FUNCTION_FNV1a_H
#define CREATOR_FUNCTION_FNV1a_H

#include "fnv1a.h"
#include "creatorFamily.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Function)
BEGIN_NAMESPACE(FNV1a)

class Creator : public Family::Creator
{
public:
    virtual const Product &create() const override {
        return Product::getInstance();
    }
};

END_NAMESPACE //  FNV1a
END_NAMESPACE //  Function
END_NAMESPACE //  Hash
END_NAMESPACE //  BusinessLogic

#endif // !CREATOR_FUNCTION_FNV1a_H
