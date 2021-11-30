#ifndef ALGHORITHM_LINEAR_PROBING_H
#define ALGHORITHM_LINEAR_PROBING_H

#include "one.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(LinearProbing)

class Product final : public One::Product
{
private:
    /* A number that is not mutually prime to the size will not apply */
    const size_t m_coefficient;

private:
    friend Creator;
    Product(size_t coefficient) : m_coefficient(coefficient)
    {
    }

protected:
//    virtual bool isValidInput() const override {
//        return gcd(m_coefficient, size()) == 1;
//    }
    virtual size_t getFirstCoefficient(size_t convertValue) const override {
        return m_hashFunction->getHash(convertValue) % size();
    }
    virtual size_t getMultiplier(size_t) const override {
        return m_coefficient;
    }
};

END_NAMESPACE // LinearProbing
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !ALGHORITHM_LINEAR_PROBING_H
