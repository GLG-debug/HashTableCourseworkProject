#ifndef CREATOR_ALGHORITHM_PSEUDORANDOM_PROBING_H
#define CREATOR_ALGHORITHM_PSEUDORANDOM_PROBING_H

#include "pseudorandomProbing.h"
#include "creatorFamily.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(PseudorandomProbing)

class Creator : public Family::Creator
{
private:
    size_t m_hashFunctionNumber;

public:
    Creator(size_t number) : m_hashFunctionNumber(number)
    {
    }

public:
    virtual std::unique_ptr<Abstract::Product> create() const override {
        return std::unique_ptr<Abstract::Product>(new Product(m_hashFunctionNumber));
    }

};

END_NAMESPACE // PseudorandomProbing
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !CREATOR_ALGHORITHM_PSEUDORANDOM_PROBING_H
