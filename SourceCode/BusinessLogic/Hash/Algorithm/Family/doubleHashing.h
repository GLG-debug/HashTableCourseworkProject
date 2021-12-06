#ifndef ALGHORITHM_DOUBLE_HASHING_H
#define ALGHORITHM_DOUBLE_HASHING_H

#include "family.h"

BEGIN_NAMESPACE(BusinessLogic)
BEGIN_NAMESPACE(Hash)
BEGIN_NAMESPACE(Algorithm)
BEGIN_NAMESPACE(DoubleHashing)

class Product final : public Family::Product
{
private:
    size_t m_firstHashFunction;
    size_t m_secondHashFunction;
    size_t m_multiplier;
private:
    friend Creator;
    Product(size_t first, size_t second) : m_firstHashFunction(first), m_secondHashFunction(second)
    {
        if (first == second) {
            throw std::invalid_argument("hash functions must be different");
        }
    }

protected:
    virtual size_t getFirstCoefficient() override {
        m_multiplier = m_hashFunction->getHash(m_convertValue, m_firstHashFunction);
        return m_hashFunction->getHash(m_convertValue, m_firstHashFunction);
    }
    virtual size_t getSecondCoefficient(size_t counter) override {
        return counter * m_multiplier;
    }
};

END_NAMESPACE // DoubleHashing
END_NAMESPACE // Algorithm
END_NAMESPACE // Hash
END_NAMESPACE // BusinessLogic

#endif // !ALGHORITHM_DOUBLE_HASHING_H
