#ifndef CREATOR_ALGHORITHM_QUADRATIC_PROBING_H
#define CREATOR_ALGHORITHM_QUADRATIC_PROBING_H

#include "quadraticProbing.h"
#include "creatorOne.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(QuadraticProbing)

class Creator : public One::Creator
{
public:
    Creator()
    {
    }

public:
    virtual std::unique_ptr<Abstract::Product> create() const override {
        return std::unique_ptr<Abstract::Product>(new Product());
    }
};

END_NAMESPACE // LinearProbing
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !CREATOR_ALGHORITHM_QUADRATIC_PROBING_H
