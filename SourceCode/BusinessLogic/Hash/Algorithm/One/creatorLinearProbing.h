#ifndef CREATOR_ALGHORITHM_LINEAR_PROBING_H
#define CREATOR_ALGHORITHM_LINEAR_PROBING_H

#include "linearProbing.h"
#include "creatorOne.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(LinearProbing)

class Creator : public One::Creator
{
private:
    /* A number that is not mutually prime to the size will not apply */
    const size_t m_coefficient;

public:
    Creator(size_t coefficient = 1) : m_coefficient(coefficient)
    {
    }

public:
    virtual std::unique_ptr<Abstract::Product> create() const override {
        return std::unique_ptr<Abstract::Product>(new Product(m_coefficient));
    }
    
};

END_NAMESPACE // LinearProbing
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !CREATOR_ALGHORITHM_LINEAR_PROBING_H
