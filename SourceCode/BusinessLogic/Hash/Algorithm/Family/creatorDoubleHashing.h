#ifndef CREATOR_ALGHORITHM_DOUBLE_HASHING_H
#define CREATOR_ALGHORITHM_DOUBLE_HASHING_H

#include "doubleHashing.h"
#include "creatorFamily.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(DoubleHashing)

class Creator : public Family::Creator
{
private:
    size_t m_firstHashFunction;
    size_t m_secondHashFunction;

public:
    Creator(size_t first, size_t second) : m_firstHashFunction(first), m_secondHashFunction(second)
    {
    }

public:
    virtual std::unique_ptr<Abstract::Product> create() const override {
        return std::unique_ptr<Abstract::Product>(new Product(m_firstHashFunction, m_secondHashFunction));
    }
};

END_NAMESPACE // DoubleHashing
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !CREATOR_ALGHORITHM_DOUBLE_HASHING_H
