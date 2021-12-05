#ifndef ALGHORITHM_PSEUDORANDOM_PROBING_H
#define ALGHORITHM_PSEUDORANDOM_PROBING_H

#include "family.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(PseudorandomProbing)

class Product final : public Family::Product
{
private:
    size_t m_hashFunctionNumber;

private:
    friend Creator;
    Product(size_t number) : m_hashFunctionNumber(number)
    {
    }

protected:
//    virtual bool isValidInput() const override {
//        return isPrimeNumber(size());
//    }
    virtual size_t getFirstCoefficient() const override {
        return m_hashFunction->getHash(m_convertValue, m_hashFunctionNumber);
    }
    virtual size_t getMultiplier(size_t counter) const override {
        size_t firstCoefficient = getFirstCoefficient();
        size_t size = this->size();
        size_t result;
        do { // Pseudo-random function
            result = m_hashFunction->getHash(m_convertValue, firstCoefficient++);
        } while (result % size == 0);
        return counter * result;
    }
};

END_NAMESPACE // PseudorandomProbing
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !ALGHORITHM_PSEUDORANDOM_PROBING_H
