#ifndef ALGHORITHM_PSEUDORANDOM_PROBING_H
#define ALGHORITHM_PSEUDORANDOM_PROBING_H

#include "family.h"

#include <random>

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(PseudorandomProbing)

class Product final : public Family::Product
{
private:
    size_t m_hashFunctionNumber;
    size_t m_multiplier;

private:
    friend Creator;
    Product(size_t number) : m_hashFunctionNumber(number)
    {
    }

protected:
//    virtual bool isValidInput() const override {
//        return isPrimeNumber(size());
//    }
    virtual size_t getFirstCoefficient() override {
        m_multiplier = m_hashFunction->getHash(m_convertValue, m_hashFunctionNumber);
        srand(m_multiplier);
        return m_hashFunction->getHash(m_convertValue, m_hashFunctionNumber);
    }
    virtual size_t getSecondCoefficient(size_t counter) override {
        return counter * rand();
    }
};

END_NAMESPACE // PseudorandomProbing
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !ALGHORITHM_PSEUDORANDOM_PROBING_H
