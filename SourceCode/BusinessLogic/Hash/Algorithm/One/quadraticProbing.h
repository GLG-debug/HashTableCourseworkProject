#ifndef ALGHORITHM_QUADRATIC_PROBING_H
#define ALGHORITHM_QUADRATIC_PROBING_H

#include "one.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(QuadraticProbing)

class Product final : public One::Product
{
private:
    friend Creator;
    Product()
    {
    }

protected:
//    virtual bool isValidInput() const override {
//        return isPrimeNumber(size());
//    }
    virtual size_t getFirstCoefficient() const override {
        return m_hashFunction->getHash(m_convertValue);
    }
    virtual size_t getMultiplier(size_t counter) const override {
        return std::pow(size(), counter);
    }
};

END_NAMESPACE // LinearProbing
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !ALGHORITHM_QUADRATIC_PROBING_H
